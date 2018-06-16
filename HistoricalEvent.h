#ifndef HISTORICALEVENT_H
#define HISTORICALEVENT_H

#include <QString>

class HistoricalEvent
{
public:
    HistoricalEvent(const QString &text, const double ocurrenceTime);

    QString text;
    double ocurrenceTime;
};

#endif // HISTORICALEVENT_H
