#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtWidgets>
#include "game.h"
#include "mainwindow.h"


game::game(int x, int y, int width, int height) //constructor
{
    QColor color(125, 0, 0);

    if(rand() % 100 < 50)
    {
        color.setRgb(0,150,0);
        set_status(true);
    }
    else
    {
        color.setRgb(255,255,255);
        set_status(false);
    }
    color_ = color;
    x_ = x * width;
    y_ = y * height;
    width_ = width;
    height_ = height;

}

void game::kill(){
    if(!is_alive){
        return;
    }
    is_alive = false;
    QColor newColorD(255,255,255);
    color_ = newColorD;

    emit killCell(this);
    update();
}
void game::revive(){
    if(is_alive){
        return;
    }
    is_alive = true;
    QColor newColorA(0,150,0);
    color_ = newColorA;

    emit reviveCell(this);
    update();
}


QRectF game::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);

}

QPainterPath game::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;

}

void game::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(widget)


    painter->setBrush(QBrush(color_));
    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));


}

void game::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        if(!this->get_status())
        {
            qDebug() << "Dead Cell";

        }
        else{
            qDebug() << "You killed this cell";
            this->set_status(false);
            QColor newColorD(255, 255, 255);
            color_ = newColorD;


            emit killCell(this);
        }
    }
    else if(event->button() == Qt::LeftButton)
    {
        if(!this->get_status())
        {
            qDebug() << "Cell has been revived";
            QColor newColorA(0,150,0);
            color_ = newColorA;
            this->set_status(true);


            emit reviveCell(this);
        }
        else{
            qDebug() << "Cell is alive";
        }
    }
    update();
}

Bar::Bar(const int x, const int y, int h) //constructor
{
    x_ = x;
    y_ = y;
    height_ = -h;
    color = "white";
    color.setRgb(0,150,0); //setting color for bars to green



}

QRectF Bar::boundingRect() const
{
    return QRectF(x_, y_, width_, height_); //gets rectangle
}

QPainterPath Bar::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem * item, QWidget *widget)
{
        Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color));
    painter->drawRect(this->x_, this->y_, this->width_, this->height_); //making rect
    painter->setBrush(b);
}







    //rules
    //Any live cell with fewer than two live neighbors dies
    //Any live cell with two or three liev neighbors remainsa alive(stable)
    //Any live cell with more than three neighbors dies(overpopulation)
    //Any dead cell with exactly three live niehgbors becomes a live cell

    //cells initalize with 50% chance of being alive or dead
