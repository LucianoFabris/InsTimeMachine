#include "TimeLineBar.h"

#include <QPainter>
#include <QRect>
#include <QFont>
#include <QDebug>
#include <MQTTAsync.h>
#include <MQTTClient.h>
#include <MQTTClientPersistence.h>

const int TIME_TO_PERCURR_BAR = 80000;

TimeLineBar::TimeLineBar(QWidget *parent) :
    QFrame(parent),
    mMargin(16),
    mCurrentTime(0),
    mHistoryLength(400),
    mIndicatorAnimation(this, "time"),
    mMovingDirection(Stoped),
    mLastEventReached(0)
{
    mIndicatorAnimation.setDuration(10000);
    mIndicatorAnimation.setEasingCurve(QEasingCurve::Linear);
    connect(&mIndicatorAnimation, &QPropertyAnimation::finished, [this]  {
       mMovingDirection = Stoped;
    });
}

int TimeLineBar::barWidth() const {
    return width() - 2*mMargin;
}

int TimeLineBar::barHeight() const {
    return height() - 2*mMargin;
}

void TimeLineBar::setGeologicalPeriodsModel(GeologicalPeriodsModel &model) {
    mGeologicalPeriodsModel = &model;
    mGeologicalPeriods = model.getAllPeriods();
    mCurrentPeriodPos = 0;
    updateHistoryLengthAndCurrentTime();
    update();
}

void TimeLineBar::updateHistoryLengthAndCurrentTime()
{
    mHistoryBeginTime = mGeologicalPeriods.first().beginTime;
    mCurrentTime = mHistoryBeginTime;
    mHistoryLength = mGeologicalPeriods.last().endTime - mHistoryBeginTime;
}

void TimeLineBar::setHistoricalEventsModel(HistoricalEventsModel &model) {
    mHistoryEventsModel = &model;
    mHistoricalEvents = mHistoryEventsModel->getAllEvents();
    checkForEvents(mCurrentTime);
}

void TimeLineBar::stopIndicator() {
    mIndicatorAnimation.stop();
    mMovingDirection = Stoped;
}

void TimeLineBar::startAnimationTo(const double endValue)
{
    mIndicatorAnimation.stop();
    updateIndicatorAnimation(endValue);
    mIndicatorAnimation.start();
}

void TimeLineBar::updateIndicatorAnimation(const double endValue) {
    mIndicatorAnimation.setDuration(TIME_TO_PERCURR_BAR*((std::abs(mCurrentTime-endValue))/(mHistoryLength)));
    mIndicatorAnimation.setStartValue(mCurrentTime);
    mIndicatorAnimation.setEndValue(endValue);
}

void TimeLineBar::moveIndicatorToLeft() {
    if(mMovingDirection != Left) {
        startAnimationTo(mHistoryBeginTime);
        mMovingDirection = Left;
    }
}

void TimeLineBar::moveIndicatorToRight() {
    if(mMovingDirection != Right) {
        startAnimationTo(mHistoryLength);
        mMovingDirection = Right;
    }
}

void TimeLineBar::setHistoryLength(const double timeDistance) {
    mHistoryLength = timeDistance;
    update();
}

void TimeLineBar::checkForEvents(const double currentTime) {
    if((currentTime > mCurrentTime) &&
       (&mHistoricalEvents[mLastEventReached] != &mHistoricalEvents.last()) &&
       ocurredInIntervalOfTolerance(mHistoricalEvents[mLastEventReached+1].ocurrenceTime,currentTime)) {
        emit eventReached(mHistoryEventsModel->index(++mLastEventReached));
    }/* else if((currentTime < mCurrentTime) &&
              (&mHistoricalEvents[mLastEventReached] != &mHistoricalEvents.first()) &&
              ocurredInIntervalOfTolerance(mHistoricalEvents[mLastEventReached-1].ocurrenceTime,currentTime)) {
        emit eventReached(mHistoryEventsModel->index(--mLastEventReached));
    }*/
    if((currentTime < mCurrentTime) &&
                  (&mHistoricalEvents[mLastEventReached] != &mHistoricalEvents.first()) &&
                  ocurredInIntervalOfTolerance(mHistoricalEvents[mLastEventReached-1].ocurrenceTime,currentTime)) {
            emit eventReached(mHistoryEventsModel->index(--mLastEventReached));
    }
}

bool TimeLineBar::ocurredInIntervalOfTolerance(const double ocurrenceTime, const double currentTime) {
    const double onePercentOfHistory = mHistoryLength / 300;
    return (currentTime >= (ocurrenceTime - onePercentOfHistory)) && (currentTime <= (ocurrenceTime + onePercentOfHistory));
}

void TimeLineBar::checkGeologicalPeriod(const double currentTime)
{
    if(currentTime > mCurrentTime && mGeologicalPeriods[mCurrentPeriodPos].before(mCurrentTime)) {
        mCurrentPeriodPos++;
        emit periodChanged(mGeologicalPeriodsModel->index(mCurrentPeriodPos));
    } else if(currentTime < mCurrentTime && mGeologicalPeriods[mCurrentPeriodPos].after(mCurrentTime)) {
        mCurrentPeriodPos--;
        emit periodChanged(mGeologicalPeriodsModel->index(mCurrentPeriodPos));
    }
}

void TimeLineBar::setCurrentTime(const double currentTime) {
    checkGeologicalPeriod(currentTime);
    checkForEvents(currentTime);
    mCurrentTime = currentTime;
    update();
}

void TimeLineBar::handleVelocity(const int velocity) {
    if(velocity >= -200 && velocity <= 200) {
        stopIndicator();
    } else if (velocity < -100) {
        moveIndicatorToRight();
    } else {
        moveIndicatorToLeft();
    }
}

void TimeLineBar::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter p(this);
    p.translate(mMargin, mMargin);
    p.save();
    drawTimeLine(p);
    p.restore();
    drawTimePositionIndicator(p);
}

void TimeLineBar::drawTimeLine(QPainter &p) const {
    if(mGeologicalPeriods.size() != 0) {
        for(const GeologicalPeriod &period : mGeologicalPeriods) {
            drawPeriod(period, p);
        }
    } else {
        p.setBrush(QBrush(QColor(Qt::red)));
        p.drawRect(0, 0, barWidth(), barHeight());
    }
}

void TimeLineBar::drawPeriod(const GeologicalPeriod &period, QPainter &p) const {
    const double periodLength = period.endTime - period.beginTime;
    const double periodLengthPercentage = periodLength / mHistoryLength;
    const double xPosPercentage = period.beginTime / mHistoryLength;
    QRect periodRect(xPosPercentage * barWidth(), 0, periodLengthPercentage * barWidth(), barHeight());
    drawPeriodRectangle(periodRect, period.color, p);
    drawPeriodName(p, periodRect, period.name);
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
    font.setPointSize(12);
    p.setFont(font);
    p.setPen(QColor(Qt::white));
    p.drawText(periodRect, periodName, QTextOption(Qt::AlignCenter));
}

void TimeLineBar::drawTimePositionIndicator(QPainter &p) const {
    const double xPostPercentage = mCurrentTime / mHistoryLength;
    p.setBrush(QBrush(QColor(Qt::white)));
    const int indicatorWidth = 16;
    const int indicatorHeight = barHeight() + 16;
    const double indicatorX = xPostPercentage * barWidth() -indicatorWidth/2;
    const double indicatorY = -8;
    p.drawRect(indicatorX, indicatorY, indicatorWidth, indicatorHeight);
    //drawIndicatorTime(p, indicatorX, indicatorY, indicatorWidth, indicatorHeight);
}

void TimeLineBar::drawIndicatorTime(QPainter &p, const double indicatorX, const double indicatorY, const int indicatorWidth, const int indicatorHeight) const {
    p.rotate(90);
    p.translate(0, -indicatorWidth);
    p.setPen(QColor(Qt::black));

    QFont f;
    f.setBold(true);
    f.setPointSize(11);
    p.setFont(f);

    p.drawText(QRect(indicatorY, -indicatorX, indicatorHeight, indicatorWidth), QString::number(mCurrentTime) + " m.a.", QTextOption(Qt::AlignCenter));
}
