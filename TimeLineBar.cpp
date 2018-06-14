#include "TimeLineBar.h"

#include <QPainter>
#include <QRect>
#include <QFont>
#include <QDebug>

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
        checkGeologicalPeriod();
    }
}

void TimeLineBar::moveIndicatorToRight() {
    if(mCurrentTime < mTimeDistance) {
        setCurrentTime(mCurrentTime + 1);
        checkGeologicalPeriod();
    }
}

void TimeLineBar::setTimeDistance(const double timeDistance) {
    mTimeDistance = timeDistance;
    update();
}

void TimeLineBar::setCurrentTime(const double currentTime) {
    mCurrentTime = currentTime;
    emit currentTimeChanged();
    update();
}

void TimeLineBar::appendGeologicalPeriod(GeologicalPeriod period) {
    mTimePeriods.append(period);
    checkGeologicalPeriod();
    update();
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

void TimeLineBar::checkGeologicalPeriod() {
    // could make a binary search
    for(const GeologicalPeriod &period : mTimePeriods) {
        if(period.contains(mCurrentTime) && mCurrentGeologicalPeriod != period.mPeriodName) {
            mCurrentGeologicalPeriod = period.mPeriodName;
            emit currentPeriodChanged(mCurrentGeologicalPeriod);
            return;
        }
    }
}

void TimeLineBar::drawTimeLine(QPainter &p) const {
    p.translate(margin, margin);
    if(mTimePeriods.size() != 0) {
        for(const GeologicalPeriod &period : mTimePeriods) {
            drawPeriod(period, p);
        }
    } else {
        p.setBrush(QBrush(QColor(Qt::red)));
        p.drawRect(0, 0, barWidth(), barHeight());
    }
}

void TimeLineBar::drawPeriod(const GeologicalPeriod &period, QPainter &p) const {
    const double timeDuration = period.mEndTime - period.mBeginingTime;
    const double timePercentage = timeDuration / mTimeDistance;
    const double xPercentage = period.mBeginingTime / mTimeDistance;
    QRect periodRect(xPercentage * barWidth(), 0, timePercentage * barWidth(), barHeight());
    drawPeriodRectangle(periodRect, period.mPeriodColor, p);
    drawPeriodName(p, periodRect, period.mPeriodName);
}

void TimeLineBar::drawPeriodRectangle(const QRect &periodRect, const QColor &color, QPainter &p) const {
    p.setBrush(color);
    const int rectBordWidth = 4;
    p.setPen(QPen(QBrush(QColor(Qt::black)), rectBordWidth));
    p.drawRect(periodRect);
}

void TimeLineBar::drawPeriodName(QPainter &p, const QRect &periodRect, const QString &periodName) const {
    QFont font;
    font.setBold(true);
    font.setPointSize(16);
    p.setFont(font);
    p.setPen(QColor(Qt::white));
    p.drawText(periodRect, periodName, QTextOption(Qt::AlignCenter));
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
