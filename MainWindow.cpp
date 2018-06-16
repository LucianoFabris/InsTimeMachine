#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mGeologicalPeriodsModel(),
    mHistoryEventsModel()
{
    ui->setupUi(this);

    connect(ui->timeLineBar, &TimeLineBar::eventReached, ui->timeDescriptionWidget, &EventDescriptionView::setCurrentEvent);
    connect(ui->timeLineBar, &TimeLineBar::periodChanged, ui->earthWidget, &EarthWidget::setEarthPeriod);

    ui->timeLineBar->setGeologicalPeriodsModel(mGeologicalPeriodsModel);
    ui->timeLineBar->setHistoricalEventsModel(mHistoryEventsModel);

    ui->earthWidget->setFocusPolicy(Qt::NoFocus);
    ui->timeDescriptionWidget->setFocusPolicy(Qt::NoFocus);
    setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_D:
        ui->timeLineBar->moveIndicatorToRight();
        break;
    case Qt::Key_A:
        ui->timeLineBar->moveIndicatorToLeft();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}
