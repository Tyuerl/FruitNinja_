#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <fstream>
#include <iostream>
class IsServer: public QTcpServer
{

public:
    IsServer();
    QTcpSocket *mlsSocket;

private:
    QByteArray mlsData;
    QString     Record;
    void isSendToClient();

public slots:
    void isConnection(qintptr socket);
    void incomingConnection(qintptr handle) override;
    void isSlotRead();
};

#endif // SERVER_H
