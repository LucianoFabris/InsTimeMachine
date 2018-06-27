#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GeologicalPeriodsModel.h"
#include "HistoryEventsModel.h"
#include "EventDescriptionView.h"
#include <QThread>
#include <QSharedPointer>

#include "ShiftrClient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GeologicalPeriodsModel mGeologicalPeriodsModel;
    HistoricalEventsModel mHistoryEventsModel;
    EventDescriptionView mDescriptionDialog;
    bool isDescriptionVisible;
    QThread mWebThread;
    ShiftrClient *mClient;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
