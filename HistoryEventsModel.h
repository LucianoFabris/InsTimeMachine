#ifndef HISTORYEVENTSMODEL_H
#define HISTORYEVENTSMODEL_H

#include <QAbstractListModel>
#include "HistoricalEvent.h"
#include <QList>

class HistoricalEventsModel : public QAbstractListModel
{
public:
    HistoricalEventsModel();

    enum Role {
        TextRole,
        TimeRole
    };

    QList<HistoricalEvent> getAllEvents() const { return mHistoryEvents; }

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;


private:
    QList<HistoricalEvent> mHistoryEvents;
};

#endif // HISTORYEVENTSMODEL_H
