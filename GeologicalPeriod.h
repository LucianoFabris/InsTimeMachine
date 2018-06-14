#ifndef GEOLOGICALPERIOD_H
#define GEOLOGICALPERIOD_H

#include <QString>
#include <QColor>

class GeologicalPeriod
{
public:
    GeologicalPeriod(QString name = "name", QColor color = Qt::red, double begining = 0, double end = 100);

    bool contains(const int time) const { return (time >= mBeginingTime && time <= mEndTime); }

    QString mPeriodName;
    QColor mPeriodColor;
    double mBeginingTime;
    double mEndTime;
};

#endif // GEOLOGICALPERIOD_H
