#include "GeologicalPeriod.h"

GeologicalPeriod::GeologicalPeriod(const QString name,
                                   const QColor color,
                                   const double begining,
                                   const double end,
                                   const QString texture) :
    name(name),
    color(color),
    beginTime(begining),
    endTime(end),
    texture(texture)
{

}
