#include "GeologicalPeriodsModel.h"

GeologicalPeriodsModel::GeologicalPeriodsModel()
{
    mPeriods.append(GeologicalPeriod("Hadeano", Qt::red, 0, 700, QStringLiteral("qrc:/volcanic-texture.png")));
    mPeriods.append(GeologicalPeriod("Arqueano", QColor(254,184,114), 700, 2250, QStringLiteral("qrc:/arquean-earth.jpg")));
    mPeriods.append(GeologicalPeriod("Proterozóico", QColor(111,218,237), 2250, 4250, QStringLiteral("qrc:/Icy-texture.png")));
    mPeriods.append(GeologicalPeriod("Fanerozoico", Qt::blue, 4250, 4700, QStringLiteral("qrc:/earth-texture.jpg")));
//    mPeriods.append(GeologicalPeriod("Neoachean", QColor(254,166,186), 1900, 2100, QStringLiteral("qrc:/arquean-earth.jpg")));
//    mPeriods.append(GeologicalPeriod("Paleoproterozoic", QColor(254,91,113), 2100, 3000, QStringLiteral("qrc:/arquean-earth.jpg")));
//    mPeriods.append(GeologicalPeriod("Mesoproterozoic", QColor(254,184,114), 3000, 3600, QStringLiteral("qrc:/earth-texture.jpg")));
//    mPeriods.append(GeologicalPeriod("Neoproterozoic", QColor(254,183,87), 3600, 4050, QStringLiteral("qrc:/Icy-texture.png")));
//    mPeriods.append(GeologicalPeriod("Paleozoic", QColor(146,195,160), 4050, 4250, QStringLiteral("qrc:/earth-texture.jpg")));
//    mPeriods.append(GeologicalPeriod("Mesozoic", QColor(7,202,234), 4250, 4400, QStringLiteral("qrc:/earth-texture.jpg")));
//    mPeriods.append(GeologicalPeriod("Cenozoic", QColor(246,236,57), 4400, 4600, QStringLiteral("qrc:/earth-texture.jpg")));
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
