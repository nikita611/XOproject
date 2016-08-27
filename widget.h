#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    int in(QPointF pn);
    char win();
    void paint(int n, QPointF* p);
    ~Widget();
public slots:
    void quit();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    bool XO;
    std::map<int,char> checkedXO;
    int step;


protected:
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // WIDGET_H
