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
    void setModel(GeologicalPeriodsModel &model);

public slots:
    void setEarthPeriod(const QModelIndex &index);

private:
    Planet *earth;
    Planet *moon;
    GeologicalPeriodsModel *model;
};

#endif // EARTHWIDGET_H
