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
    ui->timeDescriptionWidget->setHtml("<h1>Birth of a planet</h1><body style=\"text-align:center;margin:20;\">Earth grew from a cloud of dust and rocks surrounding the young Sun. Earth formed when some of these rocks collided. Eventually they were massive enough to attract other rocks with the force of gravity, and vacuumed up all the nearby junk, becoming the Earth. The Moon probably formed soon after, when a planet-sized chunk of rock smashed into the Earth and threw up a huge cloud of debris. This condensed into the Moon.</div>");
    ui->timeDescriptionWidget->setAlignment(Qt::AlignJustify);

    ui->earthWidget->setModel(mGeologicalPeriodsModel);

    ui->timeLineBar->setGeologicalPeriodsModel(mGeologicalPeriodsModel);
    ui->timeLineBar->setHistoryLength(400);
    connect(ui->timeLineBar, &TimeLineBar::currentPeriodChanged, ui->earthWidget, &EarthWidget::setEarthPeriod);
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
}
