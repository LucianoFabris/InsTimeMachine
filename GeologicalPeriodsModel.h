#ifndef GEOLOGICALPERIODSMODEL_H
#define GEOLOGICALPERIODSMODEL_H

#include <QAbstractListModel>
#include "GeologicalPeriod.h"

class GeologicalPeriodsModel : public QAbstractListModel
{
public:
    GeologicalPeriodsModel();

    enum Role {
        ColorRole,
        NameRole,
        TimeBeginRole,
        TimeEndRole,
        TextureRole
    };

    QList<GeologicalPeriod> getAllPeriods() const;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<GeologicalPeriod> mPeriods;

};

#endif // GEOLOGICALPERIODSMODEL_H
