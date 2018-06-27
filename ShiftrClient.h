#ifndef SHIFTRCLIENT_H
#define SHIFTRCLIENT_H

#include <QObject>
#include <QString>
#include <QtMqtt/QtMqtt>
#include <memory>

class ShiftrClient : public QObject
{
    Q_OBJECT
public:
    ShiftrClient();
    ~ShiftrClient();

public slots:
    void handleMessage(QMqttMessage msg);
    void startConsuming();
    void ping();
    void subscribe();

signals:
    void velocityReceived(const int velocity);

private:
    const QString HOST = "broker.shiftr.io";
    const QString USERNAME = "limbo_web_page";
    const QString PASSWORD = "a97ecaa814332c7a";
    const QString TOPIC = "/velocity";
    const int  QOS = 1;
    const int PORT = 1883;

    QMqttClient mClient;
    QMqttSubscription *mSub;
};

#endif // SHIFTRCLIENT_H
