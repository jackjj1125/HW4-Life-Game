#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void turnCount();
    int NeighborCount();
    bool is_alive();

public slots:
    void receive_inc();
    void receive_dec();
    void neighborSlot(int x, int y);

private slots:
    void on_restartButton_click();
    void on_playButton_click();
    void on_pauseButton_click();
    void on_slider(int value);
    void on_stepButton_click();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *BuildGrid_;
    QGraphicsScene *BuildGraph_;
    int cell_height_;
    int cell_wdith_;
    int bar_height_;
    int bar_width_;
    int turnCount_;
    int y_bar;
    double h_bar;
    double speed_ = 1.0;
    Game * cells[10][20];
    std::vector <Bar*> bars_;
};
#endif // MAINWINDOW_H
