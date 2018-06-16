#ifndef HISTORYEVENTSMODEL_H
#define HISTORYEVENTSMODEL_H

#include <QAbstractListModel>

class HistoryEventsModel : public QAbstractListModel
{
public:
    HistoryEventsModel();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

};

#endif // HISTORYEVENTSMODEL_H
