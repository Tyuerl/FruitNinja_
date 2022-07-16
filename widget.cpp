#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "YOU CLICKED";
    ui->graphicsView->setEnabled(true);
    ui->graphicsView->setHidden(true);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(1024, 576);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1024, 576);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QColor(210, 105, 30));

    ui->load->setHidden(true);
    ui->bestresult->setHidden(true);
    ui->label_2->setHidden(true);
    //



}

void Widget::GeneratorFruit()
{

    std:: srand(std::time(0));
    if (rand() % 2)
    {
        arbuz.push_front(*new Watermelon());
        scene->addItem(&arbuz[0]);
    }
    else
    {
        redApple.push_front(*new Apple());
        scene->addItem(&redApple[0]);
    }
//    qDebug() << "opopopopopo";
    //

}

void Widget::AnimationFruit()
{
    ui->hp->setNum(hp);
    ui->points->setNum((point));
    if (hp)
    {
        for(int i = 0; i < redApple.size(); i++)
        {
            if (redApple[i].IsAlive() == -1)
            {
                //free (&redApple[i]); фришить или делитать не надо, тк removeat сам запускает деструктор
                hp -=redApple[i].Hp();
                redApple.removeAt(i);
            }
            else if (redApple[i].IsAlive() == 2)
            {
                point += redApple[i].Hp();
                redApple[i].setAlive(3);
            }
            else if (redApple[i].IsAlive() == 0)
            {
                redApple.removeAt(i);
            }
            else
                redApple[i].Move();
        }
        for(int i = 0; i < arbuz.size(); i++)
        {
            if (arbuz[i].IsAlive() == -1)
            {
                //free (&arbuz[i]); фришить или делитать не надо, тк removeat сам запускает деструктор
                hp -= arbuz[i].Hp();
                arbuz.removeAt(i);
            }
            else if (arbuz[i].IsAlive() == 2)
            {
                point+= arbuz[i].Hp();
                arbuz[i].setAlive(3);
            }
            else if (arbuz[i].IsAlive() == 0)
            {
                arbuz.removeAt(i);
            }
            else
                arbuz[i].Move();
        }
    }
    else // конец игры собсна
    {
        hp = 0;
        redApple.clear();
        arbuz.clear();
        gameTime->stop();
        animationTimer->stop();
        scene->clear();
       // ui->graphicsView->close();
        ui->buttonstart->setHidden(false);
        ui->graphicsView->setHidden(true);
        ui->label_2->setHidden(false);
        if (record <  point)
        {
            ui->load->setHidden(false);
            ui->bestresult->setHidden(false);
        }
    }
    qDebug() << "artwork";
    scene->update();
}


Widget::~Widget()
{
    delete scene;
    delete gameTime;
    delete animationTimer;
    delete ui;

}

void Widget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

}


void Widget::on_buttonstart_clicked()
{
    ui->label->setEnabled(false);
    ui->load->setHidden(true);
    ui->bestresult->setHidden(true);
    ui->buttonstart->setHidden(true);
    ui->graphicsView->setHidden(false);
    redApple.push_back(*new Apple());
    scene->addItem(&redApple[0]);
    arbuz.push_back((*new Watermelon()));
    scene->addItem(&(arbuz[0]));

    hp = 50;
    point = 0;
    gameTime        = new QTimer(this);
    animationTimer  = new QTimer(this);
        connect (gameTime, SIGNAL(timeout()),
    this, SLOT(GeneratorFruit()));
        connect (animationTimer, SIGNAL(timeout()),
    this, SLOT(AnimationFruit()));
    gameTime->start(800);
    animationTimer->start(1000 / 40);
    scene->addText("HP: \nPOINTS:", QFont("Arial", 20));

    std::ifstream in;
    in.open("C:/Users/Tyu/Documents/FruitNinja_/Record.txt");
    QString s;
    std:: string t;
    std::getline(in, t);
    record = std::stoi(t);
    ui->label_2->setText("RECORD: " + QString::number(record));
}

void Widget::on_load_clicked()
{
    std::ofstream out;
    out.open("C:/Users/Tyu/Documents/FruitNinja_/Record.txt");
    if (out.is_open())
    {
        out << point;
    }
    out.close();
}
