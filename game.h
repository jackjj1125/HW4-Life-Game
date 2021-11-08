#ifndef GAME_H
#define GAME_H

#include <QColor>
#include <QGraphicsItem>

class Game : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Game(int x, int y, int width, int height);
    int get_x();
    int get_y();
    int get_width();
    int get_height();
    int get_status();
    int get_neighborStatus();
    void set_status();
    void set_NeighborStatus();
    void set_Color();

    signals:
        void increase();
        void decrease();
        void neighbors(int x, int y);

private:
    int x_;
    int y_;
    int width_;
    int height_;
    bool is_alive;
    QColor color_;



};

#endif // GAME_H
