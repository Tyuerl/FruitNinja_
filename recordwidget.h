#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>
#include <ctime>
#include <string>
#include <iostream>
#include <QTcpSocket>

namespace Ui {
class RecordWidget;
}

class RecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit            RecordWidget(QWidget *parent = nullptr);
                        ~RecordWidget();
    void                isSetRecord(int rec);
    QString             isNewRecordsToServ(std::string curRec, int mlsRecord);

private slots:
    void                on_pushButton_clicked();

    void on_load_clicked();

signals:
    void                isToMenu();

private:
    Ui::RecordWidget    *ui;
    int                 mlsRecord;
    QTcpSocket          *mlsSocket;
};

#endif // RECORDWIDGET_H
