#include "HistoryEventsModel.h"

#include <QFile>
#include <QDebug>

HistoricalEventsModel::HistoricalEventsModel()
{

    for(int i = 1; i <= 23; i++) {
        QFile file(":/text" + QString::number(i));
        file.open(QIODevice::ReadOnly);
        QString html = file.readAll();
        file.close();
        mHistoryEvents.append(HistoricalEvent(html, dateForEvent(i)));
    }

    mHistoryEvents.append(HistoricalEvent("<html style=\"text-align:center;padding:20;\"><h1>Hadeano</h1><body>Na escala de tempo geológico, o Hadeano é o éon mais antigo que começou há cerca de 4,57 bilhões, com o princípio do processo de formação dos planetas do Sistema Solar, e terminou, na Terra, há aproximadamente 3,85 bilhões de anos, quando surgiram as primeiras rochas, marcando o início do éon Arqueano. O nome \"Hadeano\" vem do grego hades, que significa \"inferno\", e foi cunhado pelo geólogo Preston Cloud para o período sobre o qual se tem pouca ou nenhuma informação geológica. Não é reconhecido pela Comissão Internacional sobre Estratigrafia da União Internacional de Ciências Geológicas no seu quadro estratigráfico internacional, por não haver rochas tão antigas, mas é um conceito amplamente aceito por outras fontes.</body></html>", 0));
    mHistoryEvents.append(HistoricalEvent("<html style=\"text-align:center;padding:20;\"><h1>Arqueano</h1><body>Na escala de tempo geológico, o Arqueano é o éon que está compreendido aproximadamente entre 3,85 bilhões de anos e 2,5 bilhões de anos atrás. O éon Arqueano sucede o éon Hadeano e precede o éon Proterozoico. O início do Arqueano é marcado pelas primeiras formas de vida unicelulares da Terra.</body></html>", 700));
    mHistoryEvents.append(HistoricalEvent("<html style=\"text-align:center;padding:20;\"><h1>Snowball Earth</h1><body>A Terra bola de neve é uma hipótese que sugere que a Terra esteve completamente coberta de gelo durante o período Criogeniano, entre 790 a 630 milhões de anos atrás. Foi desenvolvida de modo a explicar os depósitos sedimentares, normalmente considerados de origem glaciar a latitudes aparentemente tropicais na época, bem como outras características enigmáticas do registo geológico do Criogeniano. A existência desta glaciação global permanece, contudo, controversa, uma vez que vários cientistas contestam a possibilidade geofísica de um oceano completamente congelado, ou as provas geológicas em que a hipótese é baseada.</body></html>", 2250));
    mHistoryEvents.append(HistoricalEvent("<html style=\"text-align:center;padding:20;\"><h1>Fanerozoico</h1><body>Na escala de tempo geológico, o Fanerozoico (grego transliterado: phaneros significa \"visível\" e zoikos, \"vida\") é o éon geológico que abrange os últimos 542 milhões de anos. Tem início com o Cambriano na era Paleozoico com o surgimento de vários animais de concha e é o éon ao longo do qual a abundância de vida é maior.</body></html>", 4250));
}

double HistoricalEventsModel::dateForEvent(const int i) {
    switch (i) {
        case 1: return 10;
        case 2: return 1000;
        case 3: return 2300;
        case 4: return 3850;
        case 5: return 4165;
        case 6: return 4235;
        case 7: return 4270;
        case 8: return 4325;
        case 9: return 4400;
        case 10: return 4469;
        case 11: return 4480;
        case 12: return 4570;
        case 13: return 4635;
        case 14: return 4697.5;
        case 15: return 4699.8;
        case 16: return 4699.81;
        case 17: return 4699.84;
        case 18: return 4699.86;
        case 19: return 4699.88;
        case 20: return 4699.90;
        case 21: return 4699.92;
        case 22: return 4699.94;
        case 23: return 4699.96;
    }
    return 4700;
}


int HistoricalEventsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mHistoryEvents.size();
}

QVariant HistoricalEventsModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case TextRole:
        return mHistoryEvents[index.row()].text;
        break;
    case TimeRole:
        return mHistoryEvents[index.row()].ocurrenceTime;
    default:
        return QVariant();
        break;
    }
}
