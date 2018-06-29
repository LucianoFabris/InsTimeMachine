#ifndef EVENTDESCRIPTIONVIEW_H
#define EVENTDESCRIPTIONVIEW_H

#include "ImageTextBrowser.h"
#include <QDialog>
#include "HistoryEventsModel.h"
#include <QPropertyAnimation>
#include <QMediaPlayer>

class EventDescriptionView : public QDialog
{
    Q_OBJECT
public:
    EventDescriptionView(QPoint slidePoint, QWidget *parent = Q_NULLPTR);

public slots:
    void setCurrentEvent(const QModelIndex &index);
    void slideIn();
    void slideOut();

private:
    ImageTextBrowser *mTextBrowser;
    QPropertyAnimation mSlidingAnimation;
    QPropertyAnimation mFadingAnimation;
    QPoint mSlidePoint;
    QMediaPlayer mPlayer;
};

#endif // EVENTDESCRIPTIONVIEW_H
