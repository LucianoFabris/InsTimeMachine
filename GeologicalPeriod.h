#ifndef GEOLOGICALPERIOD_H
#define GEOLOGICALPERIOD_H

#include <QString>
#include <QColor>
#include <QMetaType>

class GeologicalPeriod
{
public:
    GeologicalPeriod(const QString name = "name",
                     const QColor color = Qt::red,
                     const double begining = 0,
                     const double end = 100,
                     const QString texture = "qrc:/earth-texture.jpg");

    bool contains(const int time) const { return (time >= beginTime && time <= endTime); }
    bool before(const int n) const { return endTime < n; }
    bool after(const int n) const { return beginTime > n; }

    QString name;
    QColor color;
    double beginTime;
    double endTime;
    QString texture;
};

Q_DECLARE_METATYPE(GeologicalPeriod)

#endif // GEOLOGICALPERIOD_H
