#ifndef TIMELINEBAR_H
#define TIMELINEBAR_H

#include <QFrame>
#include <QObject>
#include "HistoricalEvent.h"

#include "GeologicalPeriod.h"
#include "GeologicalPeriodsModel.h"
#include "HistoryEventsModel.h"

class TimeLineBar : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(double time MEMBER mCurrentTime READ currentTime WRITE setCurrentTime NOTIFY timeChanged)
    Q_PROPERTY(QModelIndex currentGeologicalPeriod READ currentPeriodIndex NOTIFY periodChanged)

public:
    TimeLineBar(QWidget *parent = Q_NULLPTR);

    double currentTime() const { return mCurrentTime; }
    QModelIndex currentPeriodIndex() const { return mGeologicalPeriodsModel->index(mCurrentPeriodPos); }

    void setGeologicalPeriodsModel(GeologicalPeriodsModel &mGeologicalPeriodsModel);
    void setHistoricalEventsModel(HistoricalEventsModel &mGeologicalPeriodsModel);

public slots:
    void setHistoryLength(const double timeDistance);
    void setCurrentTime(const double currentTime);
    void moveIndicatorToRight();
    void moveIndicatorToLeft();
    void checkForEvents();

signals:
    void timeChanged(const double currentTime);
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

    int barWidth() const;
    int barHeight() const;

    void updateHistoryLengthAndCurrentTime();

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
};

#endif // TIMELINEBAR_H
