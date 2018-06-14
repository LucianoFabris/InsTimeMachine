#ifndef TIMELINEBAR_H
#define TIMELINEBAR_H

#include <QFrame>
#include <QObject>

#include "GeologicalPeriod.h"

class TimeLineBar : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(double time MEMBER mCurrentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)
    Q_PROPERTY(QString currentGeologicalPeriod MEMBER mCurrentGeologicalPeriod READ currentPeriod NOTIFY currentPeriodChanged)

public:
    TimeLineBar(QWidget *parent = Q_NULLPTR);

    double currentTime() const { return mCurrentTime; }
    QString currentPeriod() const { return mCurrentGeologicalPeriod; }

    void appendGeologicalPeriod(GeologicalPeriod periodName);

public slots:
    void setTimeDistance(const double timeDistance);
    void setCurrentTime(const double currentTime);
    void moveIndicatorToRight();
    void moveIndicatorToLeft();

signals:
    void currentTimeChanged();
    void currentPeriodChanged(QString period);

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

    void checkGeologicalPeriod();

private:
    const int margin;
    double mCurrentTime;
    double mTimeDistance;
    QList<GeologicalPeriod> mTimePeriods;
    QString mCurrentGeologicalPeriod;
};

#endif // TIMELINEBAR_H
