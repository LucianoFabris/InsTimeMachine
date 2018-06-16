#include "HistoryEventsModel.h"

HistoricalEventsModel::HistoricalEventsModel()
{
    mHistoryEvents.append(HistoricalEvent("<html style=\"text-align:center;padding:20;\"><h1>Hadeano</h1><body>Na escala de tempo geológico, o Hadeano é o éon mais antigo que começou há cerca de 4,57 bilhões, com o princípio do processo de formação dos planetas do Sistema Solar, e terminou, na Terra, há aproximadamente 3,85 bilhões de anos, quando surgiram as primeiras rochas, marcando o início do éon Arqueano. O nome \"Hadeano\" vem do grego hades, que significa \"inferno\", e foi cunhado pelo geólogo Preston Cloud para o período sobre o qual se tem pouca ou nenhuma informação geológica. Não é reconhecido pela Comissão Internacional sobre Estratigrafia da União Internacional de Ciências Geológicas no seu quadro estratigráfico internacional, por não haver rochas tão antigas, mas é um conceito amplamente aceito por outras fontes.</body></html>", 0));
    mHistoryEvents.append(HistoricalEvent("<html style=\"text-align:center;padding:20;\"><h1>Arqueano</h1><body>Na escala de tempo geológico, o Arqueano é o éon que está compreendido aproximadamente entre 3,85 bilhões de anos e 2,5 bilhões de anos atrás. O éon Arqueano sucede o éon Hadeano e precede o éon Proterozoico. O início do Arqueano é marcado pelas primeiras formas de vida unicelulares da Terra.</body></html>", 101));
    mHistoryEvents.append(HistoricalEvent("<html style=\"text-align:center;padding:20;\"><h1>Snowball Earth</h1><body>A Terra bola de neve é uma hipótese que sugere que a Terra esteve completamente coberta de gelo durante o período Criogeniano, entre 790 a 630 milhões de anos atrás. Foi desenvolvida de modo a explicar os depósitos sedimentares, normalmente considerados de origem glaciar a latitudes aparentemente tropicais na época, bem como outras características enigmáticas do registo geológico do Criogeniano. A existência desta glaciação global permanece, contudo, controversa, uma vez que vários cientistas contestam a possibilidade geofísica de um oceano completamente congelado, ou as provas geológicas em que a hipótese é baseada.</body></html>", 201));
    mHistoryEvents.append(HistoricalEvent("<html style=\"text-align:center;padding:20;\"><h1>Fanerozoico</h1><body>Na escala de tempo geológico, o Fanerozoico (grego transliterado: phaneros significa \"visível\" e zoikos, \"vida\") é o éon geológico que abrange os últimos 542 milhões de anos. Tem início com o Cambriano na era Paleozoico com o surgimento de vários animais de concha e é o éon ao longo do qual a abundância de vida é maior.</body></html>", 301));
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
