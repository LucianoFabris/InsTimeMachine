#include "EventDescriptionView.h"

#include <QVBoxLayout>
#include <QRect>
#include <QGraphicsOpacityEffect>

EventDescriptionView::EventDescriptionView(QPoint slidePoint, QWidget *parent) :
    QDialog(parent),
    mTextBrowser(new ImageTextBrowser(this)),
    mSlidingAnimation(this, "geometry"),
    mSlidePoint(slidePoint)
{
    setGeometry(mSlidePoint.x(), mSlidePoint.y(), 500, 640);
    setFocusPolicy(Qt::NoFocus);
    setWindowFlag(Qt::FramelessWindowHint);

    mTextBrowser->setStyleSheet("QTextBrowser {background-color:black;color:white;padding:20;}");

    mSlidingAnimation.setDuration(2000);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    setLayout(layout);
    layout->addWidget(mTextBrowser);
}

void EventDescriptionView::slideIn() {
    mSlidingAnimation.setStartValue(QRect(- 600 - mSlidePoint.x(), y(), width(), height()));
    mSlidingAnimation.setEndValue(QRect(mSlidePoint.x(), y(), width(), height()));
    mSlidingAnimation.start();
}

void EventDescriptionView::slideOut() {
    mSlidingAnimation.setStartValue(QRect(mSlidePoint.x(), y(), width(), height()));
    mSlidingAnimation.setEndValue(QRect(- 600 - mSlidePoint.x(), y(), width(), height()));
    mSlidingAnimation.start();
}

void EventDescriptionView::setCurrentEvent(const QModelIndex &index) {
    mTextBrowser->setHtml(index.data(HistoricalEventsModel::TextRole).toString());
    mPlayer.stop();
    mPlayer.setMedia(QUrl("qrc:/" + index.data(HistoricalEventsModel::AudioRole).toString()));
    mPlayer.play();
}
