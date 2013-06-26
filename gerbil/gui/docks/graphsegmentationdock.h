#ifndef GRAPHSEGMENTATIONDOCK_H
#define GRAPHSEGMENTATIONDOCK_H

#include "ui_graphsegmentationdock.h"
#include "../model/representation.h"

#include <graphseg.h>
#include <shared_data.h>

#include <QDockWidget>

class GraphSegmentationDock : public QDockWidget, private Ui::GraphSegmentationDock
{
	Q_OBJECT
	
public:
	explicit GraphSegmentationDock(QWidget *parent = 0);
	~GraphSegmentationDock();
	

protected:
	void initUi();
	void startGraphseg();

signals:
	void requestGraphseg(representation::t, const vole::GraphSegConfig &config);

private:

};

#endif // GRAPHSEGMENTATIONDOCK_H