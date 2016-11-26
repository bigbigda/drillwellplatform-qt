#ifndef PLOTVIEW_H
#define PLOTVIEW_H

#include <QDialog>
#include "qcustomplot.h"
class PlotView : public QDialog
{
public:
    PlotView(QWidget *parent = 0);
    QCustomPlot *customPlot;
};

#endif // PLOTVIEW_H
