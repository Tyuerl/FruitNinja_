#include "menuwidget.h"
#include "ui_menuwidget.h"
#include <QDebug>

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
    connect(&mlsRecordPage, SIGNAL(isToMenu()),
            this, SLOT(isMoveToMenu()));
    connect(mlsSocket, &QTcpSocket::readyRead,
            this, &MenuWidget::isSlotRead);
    connect(mlsSocket, &QTcpSocket::disconnected,
            this, &QTcpSocket::deleteLater);
    mlsSocket->connectToHost("127.0.0.1", 2323);
}

MenuWidget::~MenuWidget()
{
    delete mlsUi;
}

void MenuWidget::on_buttonstart_clicked()
{
    qDebug() << mlsUi->stackedWidget->currentIndex();
    mlsUi->stackedWidget->setCurrentIndex(GAME_PAGE);
    mlsGamePage.isGameStart();
    //this->close();
    // mlsUi->stackedWidget->show();
}

void MenuWidget::isMoveToRecord()
{
    mlsUi->stackedWidget->setCurrentIndex(RECORD_PAGE);
    qDebug() << "game Ended";
}

void MenuWidget::isMoveToMenu()
{
    mlsUi->stackedWidget->setCurrentIndex(MENU_PAGE);
}

void MenuWidget::isSlotRead()
{
    QDataStream isIn(mlsSocket);
    isIn.setVersion(QDataStream::Qt_5_14);
    if (isIn.status()== QDataStream::Ok)
    {
        QString isStr;
        isIn >> isStr;
        mlsUi->record->setText(isStr);
    }
}

void MenuWidget::on_pushButton_clicked()
{

}

void MenuWidget::on_pushButton_2_clicked()
{
    QByteArray mlsData;
    mlsData.clear();
    QDataStream isOut(&mlsData, QIODevice::WriteOnly);
    isOut.setVersion(QDataStream::Qt_5_14);
    isOut << mlsUi->lineEdit->text();
    mlsSocket->write(mlsData);
}
