#include "ShiftrClient.h"

#include <QMessageBox>
#include <QDebug>
#include <QThread>

ShiftrClient::ShiftrClient() :
    mClient(this)
{
    startConsuming();
}

ShiftrClient::~ShiftrClient() {
    mSub->unsubscribe();
    delete mSub;
}

void ShiftrClient::startConsuming() {
    mClient.setHostname(HOST);
    mClient.setPort(PORT);
    mClient.setUsername(USERNAME);
    mClient.setPassword(PASSWORD);
    mClient.setCleanSession(true);
    mClient.connectToHost();
}

void ShiftrClient::ping() {
    mClient.requestPing();
}

void ShiftrClient::subscribe() {
    mSub = mClient.subscribe(TOPIC, QOS);
    connect(mSub, &QMqttSubscription::messageReceived, this, &ShiftrClient::handleMessage);
}

void ShiftrClient::handleMessage(QMqttMessage msg) {
    qDebug() << msg.payload().toInt() << endl;
    emit velocityReceived(msg.payload().toInt());
}
