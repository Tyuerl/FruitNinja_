#include "menuwidget.h"
#include "ui_menuwidget.h"
#include <QDebug>
#include <QDir>
#include <iostream>
#include <ctime>
#include <string>
MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    mlsUi(new Ui::MenuWidget)
{
    mlsUi->setupUi(this);
    mlsUi->stackedWidget->insertWidget(GAME_PAGE, &mlsGamePage);
    mlsUi->stackedWidget->insertWidget(RECORD_PAGE, &mlsRecordPage);
    mlsSocket = new QTcpSocket(this);
    connect(&mlsGamePage, SIGNAL(isToRecord()),
            this, SLOT(isMoveToRecord()));
    connect(&mlsGamePage, SIGNAL(isToMenu()),
            this, SLOT(isMoveToMenu()));
    connect(&mlsRecordPage, SIGNAL(isToMenu()),
            this, SLOT(isMoveToMenu()));
    connect(mlsSocket, &QTcpSocket::readyRead,
            this, &MenuWidget::isSlotRead);
    connect(mlsSocket, &QTcpSocket::disconnected,
            mlsSocket, &QTcpSocket::deleteLater);
    mlsSocket->connectToHost("127.0.0.1", 2323);

    std::ofstream isOut;
    isOut.open("rec.txt");
    isOut <<"20.07.2022 13:15:47 1320 points 20.07.2022 13:15:47 900 points 20.07.2022 13:15:47 890 points 20.07.2022 13:15:47 850 points 20.07.2022 13:15:47 830 points 20.07.2022 13:15:47 810 points 20.07.2022 13:15:47 790 points 20.07.2022 13:15:47 750 points 20.07.2022 13:15:47 720 points 20.07.2022 13:15:47 690 points";
    isOut.close();
    mlsUi->record->setText("Not connection");
}

MenuWidget::~MenuWidget()
{
    delete mlsUi;
}

void MenuWidget::on_buttonstart_clicked()
{
   // qDebug() << mlsUi->stackedWidget->currentIndex();
    //mlsUi->stackedWidget->setCurrentIndex(GAME_PAGE);


    mlsUi->stackedWidget->setCurrentIndex(GAME_PAGE);
    qDebug() << "game Started";
    mlsRecordPage.isSetRecord(220);
    mlsGamePage.isGameStart();
    //this->close();
    // mlsUi->stackedWidget->show();
}

void MenuWidget::isMoveToRecord()
{
    mlsUi->stackedWidget->setCurrentIndex(RECORD_PAGE);
    qDebug() << "game Ended";
    //mlsGamePage.isGameEnd();
    mlsRecordPage.isSetRecord(mlsGamePage.isRecord());
}

void MenuWidget::isMoveToMenu()
{
    mlsUi->stackedWidget->setCurrentIndex(MENU_PAGE);
    // mlsGamePage.isGameEnd();
}

void MenuWidget::isSlotRead()
{
    mlsUi->record->clear();
    QDataStream isIn(mlsSocket);
    isIn.setVersion(QDataStream::Qt_5_14);
    if (isIn.status()== QDataStream::Ok)
    {
        QString isStr;
        QString isResultText;
        isIn >> isStr;
        int isCounterSpaces = 0;
        for (int i = 0; i < isStr.count(); i++)
        {
            if (isStr[i] == ' ')
                isCounterSpaces++;
            if (isCounterSpaces % 4 == 0 && isStr[i] == ' ')
                isResultText += '\n';
            else
                isResultText += isStr[i];
        }
        mlsUi->record->setText(isResultText);
        std::ofstream isIn;
        isIn.open("rec.txt");
        isIn << isStr.QString::toStdString();
        isIn.close();
    }
}

void MenuWidget::on_pushButton_clicked()
{
    mlsUi->record->clear();
    QByteArray mlsData;
    mlsData.clear();
    QDataStream isOut(&mlsData, QIODevice::WriteOnly);
    isOut.setVersion(QDataStream::Qt_5_14);
    QString isTemp = "sendRecords";
    isOut << isTemp;
    mlsSocket->write(mlsData);
}

void MenuWidget::on_pushButton_2_clicked()
{


    //std::ifstream isIn;
    //isIn.open("rec.txt");
    //std::string isT;
    //isIn >> isT;
    //std::time_t isTime = std::time(nullptr);
    //std::tm* isNow = std::localtime(&isTime);
    //char buffer[20];
    //strftime(buffer, sizeof(buffer), "%m.%d.%Y %X", isNow);
    //qDebug() << buffer;
    //mlsUi->lineEdit->setText(0);
    //isIn.close();
}
// вывод
    // QByteArray mlsData;
    // mlsData.clear();
    // QDataStream isOut(&mlsData, QIODevice::WriteOnly);
    // isOut.setVersion(QDataStream::Qt_5_14);
    // isOut << mlsUi->lineEdit->text();
    // mlsSocket->write(mlsData);
    //QString::number(isNow->tm_mday) + "." +
    //QString:: number(isNow->tm_mon) + "." +
    //QString::number(isNow->tm_year) + ". " +
    //QString::number(isNow->tm_hour) + "." +
    //QString::number(isNow->tm_min)  + "." +
    //QString::number(isNow->tm_sec)
