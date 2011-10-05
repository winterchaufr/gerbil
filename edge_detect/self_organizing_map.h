#ifndef SELF_ORGANIZING_MAP_H
#define SELF_ORGANIZING_MAP_H

#include <vector>	//std library
#include "neuron.h"
#include "multi_img.h"

#include "edge_detection_config.h"

class SOM {

public:
	typedef std::vector<Neuron> Row;
	typedef std::vector<Row> Field;

	SOM(const EdgeDetectionConfig &conf, int dimension);

	virtual ~SOM() {}

	/**
	* Finds the neuron in the SOM grid which has the closest distance
	* to the given input vector and returns its position in the grid.
	*
	* @param	input Neuron to which closest neuron in SOM will be determined
	* @return	Position of the neuron in x,y coordinates
	*/
	virtual cv::Point identifyWinnerNeuron(const multi_img::Pixel &input) const;

    
    /**
    * Generates a lookup table of size "size" for the neurons in the SOM grid for faster access
    * @param  msi Pointer to the multispectral image
    */    
    void generateLookupTable(const multi_img &msi);
    
    /**
    * Returns the position of the closest neuron by searching the lookup table 
    * @param  x x coordinate to look for
    * @param  y y coordinate to look for
    * @return Position of the closest neuron in x,y coordinates
    */
    virtual cv::Point identifyWinnerNeuron(int y, int x) const;

	/**
	* Returns a pointer to the neuron at the given grid position
	*
	* @param	x x-coordinate
	* @param	y y-coordinate
	* @return	Pointer to neuron
	*/
	inline Neuron* getNeuron(int x, int y)
	{ return &neurons[y][x]; }

	// export as multi_img
	multi_img export_2d();

	//! Returns the width of the SOM grid
	inline int getWidth() { return width; }

	//! Returns the height of the SOM grid
	inline int getHeight() { return height; }

	//! Returns dimensionality of the SOM ( equal to neuron dimensionality)
	inline unsigned int getDimension() { return dim; }

	virtual void updateNeighborhood(const cv::Point &pos,
	                                const multi_img::Pixel &input,
	                                double radius, double learnRate);

protected:
	virtual void updateSingle(const cv::Point &pos, const multi_img::Pixel &input, double weight);
	virtual void updateSingle(const cv::Point3i &pos, const multi_img::Pixel &input, double weight);
	virtual void updateNeighborhood3(const cv::Point &pos,
	                                 const multi_img::Pixel &input,
	                                 double radius, double learnRate);

	Field neurons;	///< Pointer structure representing the SOM grid
	cv::Point** lookupTable; ///< pre calculated positions of closest neurons

	int dim;		///< Dimension of each neuron / the SOM
	int width;		  	///< Width of SOM grid
	int height;		  	///< Height of SOM grid
	bool graph;       ///< If graph is used
	bool umap;        ///< If weight map is used

	cv::Mat1d edgeWeights;
	const EdgeDetectionConfig &config;
};


#endif // SELF_ORGANIZING_MAP_H