#ifndef HISTORICALEVENT_H
#define HISTORICALEVENT_H

#include <QString>

class HistoricalEvent
{
public:
    HistoricalEvent(const QString &text, const double ocurrenceTime, const QString &audioFile);

    QString text;
    double ocurrenceTime;
    QString audioFile;
};

#endif // HISTORICALEVENT_H
