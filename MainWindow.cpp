#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ShiftrClient.h"

#include <QKeyEvent>
#include <QDebug>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mGeologicalPeriodsModel(),
    mHistoryEventsModel(),
    mDescriptionDialog(QPoint(8, 8), this),
    isDescriptionVisible(false),
    mClient(new ShiftrClient)
{
    ui->setupUi(this);

    connect(mClient, &ShiftrClient::velocityReceived, ui->timeLineBar, &TimeLineBar::handleVelocity);

    connect(ui->timeLineBar, &TimeLineBar::eventReached, &mDescriptionDialog, &EventDescriptionView::setCurrentEvent);
    connect(ui->timeLineBar, &TimeLineBar::periodChanged, ui->earthWidget, &EarthWidget::setEarthPeriod);

    ui->timeLineBar->setGeologicalPeriodsModel(mGeologicalPeriodsModel);
    ui->timeLineBar->setHistoricalEventsModel(mHistoryEventsModel);

    mDescriptionDialog.show();
    setFocus();
    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
    mWebThread.quit();
    mWebThread.wait();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()) {
        switch (event->key()) {
        case Qt::Key_D:
            ui->timeLineBar->moveIndicatorToRight();
            break;
        case Qt::Key_A:
            ui->timeLineBar->moveIndicatorToLeft();
            break;
        case Qt::Key_S:
            mClient->subscribe();
            qDebug() << "subscribed" << endl;
            break;
        case Qt::Key_Escape:
            showMinimized();
            break;
        default:
            QMainWindow::keyPressEvent(event);
            break;
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat() && (event->key() == Qt::Key_D || event->key() == Qt::Key_A)) {
        ui->timeLineBar->stopIndicator();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}
