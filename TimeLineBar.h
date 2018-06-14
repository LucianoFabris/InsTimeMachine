#ifndef TIMELINEBAR_H
#define TIMELINEBAR_H

#include <QFrame>
#include <QObject>

class TimeLineBar : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(double time MEMBER mCurrentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)

public:
    TimeLineBar(QWidget *parent = Q_NULLPTR);
    double currentTime() const { return mCurrentTime; }

public slots:
    void setTimeDistance(const double timeDistance);
    void setCurrentTime(const double currentTime);
    void moveIndicatorToRight();
    void moveIndicatorToLeft();

signals:
    void currentTimeChanged();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawTimeLine(QPainter &p) const;
    void drawTimePositionIndicator(QPainter &p) const;

    int barWidth() const;
    int barHeight() const;

private:
    const int margin;
    double mCurrentTime;
    double mTimeDistance;
};

#endif // TIMELINEBAR_H
