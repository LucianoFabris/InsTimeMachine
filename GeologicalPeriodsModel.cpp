#include "GeologicalPeriodsModel.h"

GeologicalPeriodsModel::GeologicalPeriodsModel()
{
    mPeriods.append(GeologicalPeriod("Hadeano", Qt::red, 0, 100, QStringLiteral("qrc:/volcanic-texture.png")));
    mPeriods.append(GeologicalPeriod("Arqueano", QColor(244, 66, 164), 100, 200, QStringLiteral("qrc:/arquean-earth.jpg")));
    mPeriods.append(GeologicalPeriod("Snowball Earth", QColor(130, 155, 237), 200, 300, QStringLiteral("qrc:/Icy-texture.png")));
    mPeriods.append(GeologicalPeriod("Now Earth", QColor(42, 170, 13), 300, 400, QStringLiteral("qrc:/earth-texture.jpg")));
}

QList<GeologicalPeriod> GeologicalPeriodsModel::getAllPeriods() const {
    return mPeriods;
}

int GeologicalPeriodsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mPeriods.length();
}

QVariant GeologicalPeriodsModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case ColorRole:
        return mPeriods[index.row()].color;
        break;
    case NameRole:
        return mPeriods[index.row()].name;
        break;
    case TimeBeginRole:
        return mPeriods[index.row()].beginTime;
        break;
    case TimeEndRole:
        return mPeriods[index.row()].endTime;
        break;
    case TextureRole:
        return mPeriods[index.row()].texture;
    default:
        return QVariant();
    }
}
