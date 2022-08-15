#include "server.h"
#include <QDataStream>
#include <iostream>
IsServer::IsServer()
{
    if (this->listen(QHostAddress::Any, 2323))
    {
        qDebug() << "server work";
    }
    else
    {
        qDebug() << "some errors";
    }
    std::ofstream isIn;
    isIn.open("rec.txt");
    isIn << "20.07.2022 13:15:47 1320 points 20.07.2022 13:15:47 900 points 20.07.2022 13:15:47 890 points 20.07.2022 13:15:47 850 points 20.07.2022 13:15:47 830 points 20.07.2022 13:15:47 810 points 20.07.2022 13:15:47 790 points 20.07.2022 13:15:47 750 points 20.07.2022 13:15:47 80 points 20.07.2022 13:15:47 50 points ";
    isIn.close();


    //std::ifstream isIn1;
    //isIn1.open("rec.txt");
    //std::string isTemp;
    //while (!isIn1.eof())
    //{
    //    getline(isIn1, isTemp);
    //    Record += QString::fromStdString(isTemp);
    //    //Record.push_back('\n');
    //}
    //
    //isIn1.close();
}


void IsServer::incomingConnection(qintptr handle)
{
    mlsSocket = new QTcpSocket();
    mlsSocket->setSocketDescriptor(handle);
    connect(mlsSocket, &QTcpSocket::readyRead,
            this, &IsServer::isSlotRead);
    connect(mlsSocket, &QTcpSocket::disconnected,
            mlsSocket, &QTcpSocket::deleteLater);
    qDebug() << "client connected";
    isSendToClient();

}

void IsServer::isSendToClient()
{
    Record = "";
    std::ifstream isIn1;
    isIn1.open("rec.txt");
    std::string isTemp;
    while (!isIn1.eof())
    {
        getline(isIn1, isTemp);
        Record += QString::fromStdString(isTemp);
        //Record.push_back('\n');
    }
    isIn1.close();
    qDebug() << Record;

    mlsData.clear();
    QDataStream isOut(&mlsData, QIODevice::WriteOnly);
    isOut.setVersion(QDataStream::Qt_5_14);
    isOut << Record;
    mlsSocket->write(mlsData);

}



void IsServer::isSlotRead()
{
    mlsSocket = (QTcpSocket*)sender();
    QDataStream in(mlsSocket);
    in.setVersion(QDataStream::Qt_5_14);
    if (in.status() == QDataStream::Ok)
    {
        qDebug() << "reading";
        QString isStr;
        in >> isStr;
        qDebug() << isStr;
        if (isStr == "sendRecords")
        {
            isSendToClient();
            return ;
        }
        std::ofstream isOut;
        isOut.open("rec.txt");
        isOut << isStr.QString::toStdString();
        isOut.close();
        isSendToClient();
    }
    else
    {
        qDebug() << "error data stream";
    }

}


