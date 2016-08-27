#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Крестики-Нолики");

    XO = true;
    step = 0;

    scene = new QGraphicsScene();
    setFixedSize(400,300);
    scene->setSceneRect(0,0,399,299);
    scene->setBackgroundBrush(QBrush(QColor("gray")));

    QGraphicsLineItem *item1 = new QGraphicsLineItem();
    QGraphicsLineItem *item2 = new QGraphicsLineItem();
    QGraphicsLineItem *item3 = new QGraphicsLineItem();
    QGraphicsLineItem *item4 = new QGraphicsLineItem();

    item1->setLine(170,60,170,240);
    item2->setLine(230,60,230,240);
    item3->setLine(110,120,290,120);
    item4->setLine(110,180,290,180);

    checkedXO = {
        {1,'Z'},
        {2,'Z'},
        {3,'Z'},
        {4,'Z'},
        {5,'Z'},
        {6,'Z'},
        {7,'Z'},
        {8,'Z'},
        {9,'Z'}
    };

    scene->addItem(item1);
    scene->addItem(item2);
    scene->addItem(item3);
    scene->addItem(item4);

    ui->graphicsView->setScene(scene);

}

int Widget::in(QPointF pn)
{
        if(pn.x() > 110 && pn.x() < 170)
        {
            if(pn.y() > 60 && pn.y() < 120)
                return 1;
            else if(pn.y() > 120 && pn.y() < 180)
                return 4;
            else if(pn.y() > 180 && pn.y() < 240)
                return 7;
            else return 0;
        }
        if(pn.x() > 170 && pn.x() < 230)
        {
            if(pn.y() > 60 && pn.y() < 120)
                return 2;
            else if(pn.y() > 120 && pn.y() < 180)
                return 5;
            else if(pn.y() > 180 && pn.y() < 240)
                return 8;
            else return 0;
        }
        if(pn.x() > 230 && pn.x() < 290)
        {
            if(pn.y() > 60 && pn.y() < 120)
                return 3;
            else if(pn.y() > 120 && pn.y() < 180)
                return 6;
            else if(pn.y() > 180 && pn.y() < 240)
                return 9;
            else return 0;
        }
        return 0;

}

char Widget::win()
{
    if(!XO)
    {
        if((checkedXO.at(1) == 'X') && (checkedXO.at(2) == 'X') && (checkedXO.at(3) == 'X'))
            return 'X';
        if((checkedXO.at(4) == 'X') && (checkedXO.at(5) == 'X') && (checkedXO.at(6) == 'X'))
            return 'X';
        if((checkedXO.at(7) == 'X') && (checkedXO.at(8) == 'X') && (checkedXO.at(9) == 'X'))
            return 'X';

        if((checkedXO.at(1) == 'X') && (checkedXO.at(4) == 'X') && (checkedXO.at(7) == 'X'))
            return 'X';
        if((checkedXO.at(2) == 'X') && (checkedXO.at(5) == 'X') && (checkedXO.at(8) == 'X'))
            return 'X';
        if((checkedXO.at(3) == 'X') && (checkedXO.at(6) == 'X') && (checkedXO.at(9) == 'X'))
            return 'X';

        if((checkedXO.at(1) == 'X') && (checkedXO.at(5) == 'X') && (checkedXO.at(9) == 'X'))
            return 'X';
        if((checkedXO.at(3) == 'X') && (checkedXO.at(5) == 'X') && (checkedXO.at(7) == 'X'))
            return 'X';
    }

    if((checkedXO.at(1) == 'O') && (checkedXO.at(2) == 'O') && (checkedXO.at(3) == 'O'))
        return 'O';
    if((checkedXO.at(4) == 'O') && (checkedXO.at(5) == 'O') && (checkedXO.at(6) == 'O'))
        return 'O';
    if((checkedXO.at(7) == 'O') && (checkedXO.at(8) == 'O') && (checkedXO.at(9) == 'O'))
        return 'O';

    if((checkedXO.at(1) == 'O') && (checkedXO.at(4) == 'O') && (checkedXO.at(7) == 'O'))
        return 'O';
    if((checkedXO.at(2) == 'O') && (checkedXO.at(5) == 'O') && (checkedXO.at(8) == 'O'))
        return 'O';
    if((checkedXO.at(3) == 'O') && (checkedXO.at(6) == 'O') && (checkedXO.at(9) == 'O'))
        return 'O';

    if((checkedXO.at(1) == 'O') && (checkedXO.at(5) == 'O') && (checkedXO.at(9) == 'O'))
        return 'O';
    if((checkedXO.at(3) == 'O') && (checkedXO.at(5) == 'O') && (checkedXO.at(7) == 'O'))
        return 'O';

    if(step == 9)
    {
        QMessageBox::about(this, "Ничья!", "Ничья");
        quit();
    }

    return 'Z';


}

void Widget::paint(int n, QPointF* p)
{
    auto it = checkedXO.find(n);
    if(it->second == 'X' || it->second == 'O')
        return;
    if(XO)
    {
        QGraphicsLineItem *lineItem1 = new QGraphicsLineItem();
        QGraphicsLineItem *lineItem2 = new QGraphicsLineItem();
        lineItem1->setLine(p->x() - 20, p->y() - 20, p->x() + 20, p->y() + 20);
        lineItem2->setLine(p->x() - 20, p->y() + 20, p->x() + 20, p->y() - 20);
        scene->addItem(lineItem1);
        scene->addItem(lineItem2);
        checkedXO.at(n) = 'X';
        XO = !XO;
    }
    else
    {
        QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem();
        ellipse->setRect(p->x() - 20, p->y() - 20, 40, 40);
        scene->addItem(ellipse);
        checkedXO.at(n) = 'O';
        XO = !XO;
    }

    step++;

    switch(win())
    {
    case 'X':
    {
        QMessageBox::about(this, "Победа!!", "Победил Х!");
        quit();
        break;
    }
    case 'O':
    {
        QMessageBox::about(this, "Победа!!", "Победил О!");
        quit();
        break;
    }
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::quit()
{
    exit(0);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    QPointF point = event->pos();
    int cell = in(point);
    if(cell == 0)
        return;
    QPointF *pnt = new QPointF();
    switch(cell)
    {

    case 1:
    {
        pnt->setX(140);
        pnt->setY(90);
        paint(cell, pnt);
        break;
    }

    case 2:
    {
        pnt->setX(200);
        pnt->setY(90);
        paint(cell, pnt);
        break;
    }

    case 3:
    {
        pnt->setX(260);
        pnt->setY(90);
        paint(cell, pnt);
        break;
    }



    case 4:
    {
        pnt->setX(140);
        pnt->setY(150);
        paint(cell, pnt);
        break;
    }

    case 5:
    {
        pnt->setX(200);
        pnt->setY(150);
        paint(cell, pnt);
        break;
    }

    case 6:
    {
        pnt->setX(260);
        pnt->setY(150);
        paint(cell, pnt);
        break;
    }



    case 7:
    {
        pnt->setX(140);
        pnt->setY(210);
        paint(cell, pnt);
        break;
    }

    case 8:
    {
        pnt->setX(200);
        pnt->setY(210);
        paint(cell, pnt);
        break;
    }

    case 9:
    {
        pnt->setX(260);
        pnt->setY(210);
        paint(cell, pnt);
        break;
    }

    }

}
