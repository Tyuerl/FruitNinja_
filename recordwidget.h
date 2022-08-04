#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>

namespace Ui {
class RecordWidget;
}

class RecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit            RecordWidget(QWidget *parent = nullptr);
                        ~RecordWidget();

private slots:
    void                on_pushButton_clicked();

signals:
    void                isToMenu();

private:
    Ui::RecordWidget    *ui;
};

#endif // RECORDWIDGET_H
