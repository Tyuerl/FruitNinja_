#include "recordwidget.h"
#include "ui_recordwidget.h"
#include "widget.h"

RecordWidget::RecordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordWidget)
{
    ui->setupUi(this);
    mlsSocket = new QTcpSocket(this);
    mlsSocket->connectToHost("127.0.0.1", 2323);
}

RecordWidget::~RecordWidget()
{
    delete ui;
}

void RecordWidget::isSetRecord(int rec)
{
    mlsRecord = rec;
}

void RecordWidget::on_pushButton_clicked()
{
    emit isToMenu();
}


QString RecordWidget::isNewRecordsToServ(std::string curRec, int mlsRecord)
{
    int isCountSpaces = -2;
    int isIndexNewRecord = 0;
    int isCurRecord = 0;
    bool isFlag = false;
    QString isNewRecords;
    int i = 0;
    for (;i < (int)curRec.length() && !isFlag; i++)
    {
        if (curRec[i] == ' ')
            isCountSpaces++;
        if (isCountSpaces % 4 == 0 && curRec[i] == ' ')
        {
            isCurRecord = std::stoi(&(curRec[i]));
            if (isCurRecord < mlsRecord)
            {
                isIndexNewRecord = i - 20;
                isFlag = true;
            }
        }
      //  isNewRecords += curRec[i];
    }
    //isNewRecords += QString::number(isCurRecord) + " points ";
    std::time_t isTime = std::time(nullptr);
    std::tm* isNow = std::localtime(&isTime);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y %X", isNow);
   // qDebug() << buffer << mlsRecord << " points ";
    isNewRecords = QString::fromStdString(curRec.substr(0, isIndexNewRecord)) + " ";
    isNewRecords += QString::fromStdString(buffer) + " " + QString::number(mlsRecord) + " points";
   // qDebug() << isNewRecords;
    int isCountLines = isCountSpaces / 4 + 1;
    isCountSpaces = -3;
    i = isIndexNewRecord;
    if (isCountLines != 10)
    {
        for (; i < (int)curRec.length() && isCountLines < 10; i++)
        {
            if (curRec[i] ==' ')
                isCountSpaces++;
            if (isCountSpaces%4 == 0 && curRec[i] == ' ')
                isCountLines++;
            isNewRecords +=curRec[i];
        }
        isNewRecords += QString::number(std::stoi(&(curRec[i]))) + " points";
    }
    isNewRecords += " ";
    qDebug() << isNewRecords;
    return (isNewRecords);
}

void RecordWidget::on_load_clicked() // saveRecord + send to server
{

    std::ifstream in;
    in.open("rec.txt");
    //in.open(QDir::currentPath().QString::toStdString() + "/rec.txt");
    QString s;
    std:: string t;
    getline(in, t);

    QByteArray mlsData;
    mlsData.clear();
    QDataStream isOut(&mlsData, QIODevice::WriteOnly);
    isOut.setVersion(QDataStream::Qt_5_14);
    isOut << isNewRecordsToServ(t, mlsRecord);
    mlsSocket->write(mlsData);
    emit isToMenu();
    //mlsUi->lineEdit->setText(0);
    //isIn.close();
}

