#ifndef TIMELINEBAR_H
#define TIMELINEBAR_H

#include <QFrame>
#include <QObject>
#include <QPropertyAnimation>
#include "HistoricalEvent.h"

#include "GeologicalPeriod.h"
#include "GeologicalPeriodsModel.h"
#include "HistoryEventsModel.h"

class TimeLineBar : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(double time MEMBER mCurrentTime READ currentTime WRITE setCurrentTime)
    Q_PROPERTY(QModelIndex currentGeologicalPeriod NOTIFY periodChanged)

    enum MovingDirection {
        Stoped,
        Right,
        Left
    };

public:
    TimeLineBar(QWidget *parent = Q_NULLPTR);

    double currentTime() const { return mCurrentTime; }
    void setGeologicalPeriodsModel(GeologicalPeriodsModel &mGeologicalPeriodsModel);
    void setHistoricalEventsModel(HistoricalEventsModel &mGeologicalPeriodsModel);

public slots:
    void setHistoryLength(const double timeDistance);
    void setCurrentTime(const double currentTime);
    void moveIndicatorToRight();
    void moveIndicatorToLeft();
    void stopIndicator();
    void handleVelocity(const int velocity);

signals:
    void periodChanged(const QModelIndex &index);
    void eventReached(const QModelIndex &index);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawTimeLine(QPainter &p) const;
    void drawTimePositionIndicator(QPainter &p) const;
    void drawPeriodName(QPainter &p, const QRect &periodRect, const QString &periodName) const;
    void drawPeriod(const GeologicalPeriod &period, QPainter &p) const;
    void drawPeriodRectangle(const QRect &periodRect, const QColor &color, QPainter &p) const;
    void drawIndicatorTime(QPainter &p, const double indicatorX, const double indicatorY, const int indicatorWidth, const int indicatorHeight) const;

    int barWidth() const;
    int barHeight() const;

    void updateHistoryLengthAndCurrentTime();
    void updateIndicatorAnimation(const double endValue);
    void startAnimationTo(const double endValue);
    void checkGeologicalPeriod(const double currentTime);
    void checkForEvents(const double currentTime);
    bool ocurredInIntervalOfTolerance(const double ocurrenceTime, const double currentTime);

private:
    const int mMargin;
    double mCurrentTime;
    double mHistoryLength;
    QList<GeologicalPeriod> mGeologicalPeriods;
    int mCurrentPeriodPos;
    QList<HistoricalEvent> mHistoricalEvents;
    GeologicalPeriodsModel *mGeologicalPeriodsModel;
    HistoricalEventsModel *mHistoryEventsModel;
    double mHistoryBeginTime;
    QPropertyAnimation mIndicatorAnimation;
    MovingDirection mMovingDirection;
    int mLastEventReached;
};

#endif // TIMELINEBAR_H
