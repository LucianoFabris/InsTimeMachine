#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timeDescriptionWidget->setHtml("<h1>Birth of a planet</h1><body>Earth grew from a cloud of dust and rocks surrounding the young Sun. Earth formed when some of these rocks collided. Eventually they were massive enough to attract other rocks with the force of gravity, and vacuumed up all the nearby junk, becoming the Earth. The Moon probably formed soon after, when a planet-sized chunk of rock smashed into the Earth and threw up a huge cloud of debris. This condensed into the Moon.</body>");
    ui->timeDescriptionWidget->setAlignment(Qt::AlignJustify);

    ui->timeLineBar->setTimeDistance(400);
    ui->timeLineBar->appendGeologicalPeriod(GeologicalPeriod("Hadeano", Qt::red, 0, 100));
    ui->timeLineBar->appendGeologicalPeriod(GeologicalPeriod("Arqueano", QColor(244, 66, 164), 100, 200));
    ui->timeLineBar->appendGeologicalPeriod(GeologicalPeriod("Snowball Earth", QColor(130, 155, 237), 200, 300));
    ui->timeLineBar->appendGeologicalPeriod(GeologicalPeriod("Now Earth", QColor(42, 170, 13), 300, 400));

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
