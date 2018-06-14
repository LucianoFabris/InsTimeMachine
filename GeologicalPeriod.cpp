#include "GeologicalPeriod.h"

GeologicalPeriod::GeologicalPeriod(QString name, QColor color, double begining, double end) :
    mPeriodName(name),
    mPeriodColor(color),
    mBeginingTime(begining),
    mEndTime(end)
{

}
