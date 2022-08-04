#include "recordwidget.h"
#include "ui_recordwidget.h"
#include "widget.h"

RecordWidget::RecordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordWidget)
{
    ui->setupUi(this);
}

RecordWidget::~RecordWidget()
{
    delete ui;
}

void RecordWidget::on_pushButton_clicked()
{
    emit isToMenu();
}
