#ifndef EARTHWIDGET_H
#define EARTHWIDGET_H

#include <QWidget>
#include "Planet.h"
#include "GeologicalPeriodsModel.h"

class EarthWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EarthWidget(QWidget *parent = nullptr);

public slots:
    void setEarthPeriod(const QModelIndex &index);

private:
    Planet *earth;
    Planet *moon;

};

#endif // EARTHWIDGET_H
