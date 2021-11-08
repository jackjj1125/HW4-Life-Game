#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>

#include "game.h"

namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void turnCount(); //handles turns
    void checkAlive(); //checks if cells should be alive or dead
    int NeighborCount(); //checks neighbors
    bool is_alive(); //checks if a given cell is alive
    void PopulationCounter(int pop);
   // void receive_inc(); //
   // void receive_dec(); //
    void neighborSlot(int x, int y);

    int population_;


private slots: //buttons

 //   void on_restartButton_click(); //slot for restart game button
   // void on_playButton_click(); //slot for play game button
    //void on_pauseButton_click(); //slot for pause game button
    //void on_slider(int value); //slot for slider button

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    QGraphicsScene *MakeBoard_;
    QGraphicsScene *MakePopGraph_;

    int cell_height_;
    int cell_width_;
    int turnCounter_ = 0;
    QTimer *timer;
    game * cells[10][20];
};
#endif // MAINWINDOW_H
