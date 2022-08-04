#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , mlsUi(new Ui::Widget)
{
    mlsUi->setupUi(this);
    qDebug() << "YOU RUN APP";
    mlsUi->graphicsView->setEnabled(true);
    mlsUi->graphicsView->setHidden(true);
    mlsUi->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mlsUi->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mlsUi->graphicsView->setFixedSize(1024, 576);
    mlsUi->graphicsView->setRenderHint(QPainter::Antialiasing);
    mlsScene = new QGraphicsScene();
    mlsScene->setSceneRect(0, 0, 1024, 576);
    mlsUi->graphicsView->setScene(mlsScene);
    mlsUi->graphicsView->setBackgroundBrush(BROWN);
    mlsUi->bestresult->setHidden(true);
    mlsUi->bestresult->setHidden(true);
    mlsUi->graphicsView->setHidden(false);
    mlsFruit.push_back(new IsApple());
    mlsScene->addItem(mlsFruit[0]);
    mlsHp = 5;
    mlsPoint = 0;
    mlsScene->addText("HP: \nPOINTS:", QFont("Arial", 20));
    std::ifstream in;
    in.open("C:/Users/Tyu/Documents/FruitNinja_/rec.txt");
    QString s;
    std:: string t;
    std::getline(in, t);
    mlsRecord = std::stoi(t);

}

void Widget::isGeneratorFruit()
{

    std:: srand(std::time(0));
    if (rand() % 2)
    {
        mlsFruit.push_front(new IsWatermelon());

    }
    else
    {
       mlsFruit.push_front(new IsApple());
    }
    mlsScene->addItem(mlsFruit[0]);
//    qDebug() << "opopopopopo";
    //

}

void Widget::isAnimationFruit()
{
    mlsScene->update();
    if (mlsHp > 0)
    {
        for(int i = 0; i < mlsFruit.size(); i++)
        {
            if (mlsFruit[i]->isAlive(0) == IsFruit::isDamaging)
            {
                //free (&mlsFruit[i]); фришить или делитать не надо, тк removeat сам запускает деструктор
                mlsHp -= mlsFruit[i]->isHp();
                mlsScene->removeItem(mlsFruit[i]);
                mlsFruit.removeAt(i);
            }
            else if (mlsFruit[i]->isAlive(0) == IsFruit::isPoint)
            {
                mlsPoint+= mlsFruit[i]->isHp();
                mlsFruit[i]->isSetAlive(IsFruit::isCutting);
            }
            else if (mlsFruit[i]->isAlive(0) == IsFruit::isDeleting)
            {
                mlsScene->removeItem(mlsFruit[i]);
                mlsFruit.removeAt(i);
            }
            else
                mlsFruit[i]->isMove();
        }
    }
    else // конец игры собсна
    {
        isGameEnd();
    }
    mlsUi->hp->setNum(mlsHp);
    mlsUi->points->setNum((mlsPoint));
}


Widget::~Widget()
{
    delete mlsScene;
    delete mlsGameTime;
    delete mlsAnimationTimer;
    delete mlsUi;

}

void Widget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

}

void Widget::isGameStart()
{

        mlsGameTime = new QTimer();
        mlsAnimationTimer = new QTimer();

    connect (mlsGameTime, SIGNAL(timeout()),
    this, SLOT(isGeneratorFruit()));
    connect (mlsAnimationTimer, SIGNAL(timeout()),
    this, SLOT(isAnimationFruit()));
    mlsGameTime->start(800);
    mlsAnimationTimer->start(1000 / 40);
    mlsHp = 5;
    mlsPoint = 0;
}

void Widget::isGameEnd()
{
    mlsHp = 0;
    mlsFruit.clear();
    mlsGameTime->stop();
    mlsAnimationTimer->stop();
    mlsScene->clear();
    delete mlsGameTime;
    delete mlsAnimationTimer;
    mlsGameTime = nullptr;
    mlsAnimationTimer = nullptr;
    //mlsUi->graphicsView->setHidden(true);
    if (mlsRecord <  mlsPoint)
    {
  //      mlsUi->bestresult->setHidden(false);
    }
    emit isToRecord();
}


void Widget::on_buttonstart_clicked()
{

    mlsUi->bestresult->setHidden(true);
    mlsUi->graphicsView->setHidden(false);
    mlsFruit.push_back(new IsApple());
    mlsScene->addItem(mlsFruit[0]);
    mlsGameTime        = new QTimer(this);
    mlsAnimationTimer  = new QTimer(this);
    mlsHp = 50;
    mlsPoint = 0;
    connect (mlsGameTime, SIGNAL(timeout()),
    this, SLOT(isGeneratorFruit()));
    connect (mlsAnimationTimer, SIGNAL(timeout()),
    this, SLOT(isAnimationFruit()));

    mlsScene->addText("HP: \nPOINTS:", QFont("Arial", 20));

  //  std::ifstream in;
  //  in.open("C:/Users/Tyu/Documents/FruitNinja_/rec.txt");
   // QString s;
   // std:: string t;
   // std::getline(in, t);
  //  mlsRecord = std::stoi(t);
}

void Widget::on_load_clicked()
{
 //   std::ofstream out;
//    out.open("C:/Users/Tyu/Documents/FruitNinja_/rec.txt");
   // if (out.is_open())
  //  {
 //       out << mlsPoint;
 //   }
 //   out.close();
}
