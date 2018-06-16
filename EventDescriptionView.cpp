#include "EventDescriptionView.h"

EventDescriptionView::EventDescriptionView(QWidget *parent) :
    QTextBrowser(parent)
{

}

void EventDescriptionView::setCurrentEvent(const QModelIndex &index) {
    setHtml(index.data(HistoricalEventsModel::TextRole).toString());
}
