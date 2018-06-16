#include "TimeLineBar.h"

#include <QPainter>
#include <QRect>
#include <QFont>
#include <QDebug>

TimeLineBar::TimeLineBar(QWidget *parent) :
    QFrame(parent),
    margin(16),
    mCurrentTime(70),
    mHistoryLength(100)
{

}

void TimeLineBar::setGeologicalPeriodsModel(GeologicalPeriodsModel &model) {
    geologicalPeriodsModel = &model;
    mGeologicalPeriods = model.getAllPeriods();
    mCurrentPeriodPos = 0;
    updateHistoryLengthAndCurrentTime();
    update();
}

void TimeLineBar::updateHistoryLengthAndCurrentTime()
{
    mHistoryBeginTime = mGeologicalPeriods[0].beginTime;
    double historyEnd = mGeologicalPeriods[0].endTime;

    for(int i = 1;i < mGeologicalPeriods.length(); i++) {
        mHistoryBeginTime = std::min(mHistoryBeginTime, mGeologicalPeriods[i].beginTime);
        historyEnd = std::max(historyEnd, mGeologicalPeriods[i].endTime);
    }

    mCurrentTime = mHistoryBeginTime;
    mHistoryLength = historyEnd - mHistoryBeginTime;
}

void TimeLineBar::setHistoricalEventsModel(HistoryEventsModel &model) {
    historyEventsModel = &model;
}

void TimeLineBar::moveIndicatorToLeft() {
    if(mCurrentTime > mHistoryBeginTime) {
        setCurrentTime(mCurrentTime - 1);
        if(mGeologicalPeriods[mCurrentPeriodPos].after(mCurrentTime)) {
            mCurrentPeriodPos--;
            emit currentPeriodChanged(geologicalPeriodsModel->index(mCurrentPeriodPos));
        }
        emit currentTimeChanged(mCurrentTime);
    }
}

void TimeLineBar::moveIndicatorToRight() {
    if(mCurrentTime < mHistoryLength) {
        setCurrentTime(mCurrentTime + 1);
        if(mGeologicalPeriods[mCurrentPeriodPos].before(mCurrentTime)) {
            mCurrentPeriodPos++;
            emit currentPeriodChanged(geologicalPeriodsModel->index(mCurrentPeriodPos));
        }
        emit currentTimeChanged(mCurrentTime);
    }
}

void TimeLineBar::setHistoryLength(const double timeDistance) {
    mHistoryLength = timeDistance;
    update();
}

void TimeLineBar::setCurrentTime(const double currentTime) {
    mCurrentTime = currentTime;
    emit currentTimeChanged(mCurrentTime);
    update();
}

void TimeLineBar::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter p(this);
    p.translate(margin, margin);
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
    const double xPostPercentage = mCurrentTime / mHistoryLength;
    p.setBrush(QBrush(QColor(Qt::white)));
    const int indicatorWidth = 16;
    const int indicatorHeight = barHeight() + 16;
    p.drawRect(xPostPercentage * barWidth() -indicatorWidth/2, -8, indicatorWidth, indicatorHeight);
}
