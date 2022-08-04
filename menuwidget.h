#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include "widget.h"
#include "recordwidget.h"
#include <QStackedWidget>
#include <QTcpSocket>
#include <QDataStream>
const int           MENU_PAGE     = 0;
const int           GAME_PAGE     = 1;
const int           RECORD_PAGE   = 2;

namespace Ui
{
class MenuWidget;
}

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit        MenuWidget(QWidget *parent = nullptr);
                    ~MenuWidget();

private slots:
    void            on_buttonstart_clicked();
    void            isMoveToRecord();
    void            isMoveToMenu();
    void            isSlotRead();
    void            on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MenuWidget  *mlsUi;
    Widget          mlsGamePage;
    RecordWidget    mlsRecordPage;
    QStackedWidget  mlsStackedWidgets;
    QTcpSocket      *mlsSocket;
    QByteArray      mlsRecord;


};

#endif // MENUWIDGET_H
