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
    Q_PROPERTY(double time MEMBER mCurrentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)
    Q_PROPERTY(QModelIndex currentGeologicalPeriod READ currentPeriodIndex NOTIFY currentPeriodChanged)

public:
    TimeLineBar(QWidget *parent = Q_NULLPTR);

    double currentTime() const { return mCurrentTime; }
    QModelIndex currentPeriodIndex() const { return geologicalPeriodsModel->index(mCurrentPeriodPos); }

    void setGeologicalPeriodsModel(GeologicalPeriodsModel &geologicalPeriodsModel);
    void setHistoricalEventsModel(HistoryEventsModel &geologicalPeriodsModel);

public slots:
    void setHistoryLength(const double timeDistance);
    void setCurrentTime(const double currentTime);
    void moveIndicatorToRight();
    void moveIndicatorToLeft();

signals:
    void currentTimeChanged(const double currentTime);
    void currentPeriodChanged(const QModelIndex &index);
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
    const int margin;
    double mCurrentTime;
    double mHistoryLength;
    QList<GeologicalPeriod> mGeologicalPeriods;
    int mCurrentPeriodPos;
    QList<HistoricalEvent> mHistoricalEvents;
    GeologicalPeriodsModel *geologicalPeriodsModel;
    HistoryEventsModel *historyEventsModel;
    double mHistoryBeginTime;
};

#endif // TIMELINEBAR_H
