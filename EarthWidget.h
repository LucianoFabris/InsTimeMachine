#ifndef EARTHWIDGET_H
#define EARTHWIDGET_H

#include <QWidget>
#include "Planet.h"

class EarthWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EarthWidget(QWidget *parent = nullptr);

signals:

public slots:
    void setEarthPeriod(const QString &period);

private:
    Planet *earth;
    Planet *moon;
};

#endif // EARTHWIDGET_H
