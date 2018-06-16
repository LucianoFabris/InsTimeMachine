#ifndef EVENTDESCRIPTIONVIEW_H
#define EVENTDESCRIPTIONVIEW_H

#include <QTextBrowser>
#include "HistoryEventsModel.h"

class EventDescriptionView : public QTextBrowser
{
    Q_OBJECT
public:
    EventDescriptionView(QWidget *parent = Q_NULLPTR);

public slots:
    void setCurrentEvent(const QModelIndex &index);

};

#endif // EVENTDESCRIPTIONVIEW_H
