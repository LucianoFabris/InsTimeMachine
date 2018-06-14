#include "TimeLineBar.h"

#include <QPainter>
#include <QRect>

TimeLineBar::TimeLineBar(QWidget *parent) :
    QFrame(parent),
    margin(16),
    mCurrentTime(70),
    mTimeDistance(100)
{

}


void TimeLineBar::moveIndicatorToLeft() {
    if(mCurrentTime > 0) {
        setCurrentTime(mCurrentTime - 1);
    }
}

void TimeLineBar::moveIndicatorToRight() {
    if(mCurrentTime < mTimeDistance) {
        setCurrentTime(mCurrentTime + 1);
    }
}

void TimeLineBar::setTimeDistance(const double timeDistance) {
    mTimeDistance = timeDistance;
    update();
}

void TimeLineBar::setCurrentTime(const double currentTime) {
    mCurrentTime = currentTime;
    emit currentTimeChanged();
    repaint();
}

void TimeLineBar::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    // Do bar Paiting
    QPainter p(this);
    p.save();
    drawTimeLine(p);
    p.restore();
    drawTimePositionIndicator(p);
}

void TimeLineBar::drawTimeLine(QPainter &p) const {
    p.setBrush(QBrush(QColor(Qt::red)));
    p.drawRect(margin, margin, barWidth(), barHeight());
}

int TimeLineBar::barWidth() const {
    return width() - 2*margin;
}

int TimeLineBar::barHeight() const {
    return height() - 2*margin;
}

void TimeLineBar::drawTimePositionIndicator(QPainter &p) const {
    const double timePercentage = mCurrentTime / mTimeDistance;
    p.setBrush(QBrush(QColor(Qt::white)));
    const int indicatorWidth = 16;
    const int indicatorHeight = barHeight() + 16;
    p.drawRect(margin + timePercentage * barWidth(), margin - 8, indicatorWidth, indicatorHeight);
}
