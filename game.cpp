#include "game.h"
#include "mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtWidgets>



game::game(int x, int y, int width, int height)
{
    QColor color(125, 0, 0);

    //rules
    //Any live cell with fewer than two live neighbors dies
    //Any live cell with two or three liev neighbors remainsa alive(stable)
    //Any live cell with more than three neighbors dies(overpopulation)
    //Any dead cell with exactly three live niehgbors becomes a live cell

    //cells initalize with 50% chance of being alive or dead




}

