#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    turnCounter_ = 0;
    QColor color(255,0,0);

    MakeBoard_ = new QGraphicsScene;
    QGraphicsView * grid_view = ui->gameGraphicsView;
    grid_view->setScene(MakeBoard_);
    grid_view->setSceneRect(0,0,grid_view->frameSize().width(),grid_view->frameSize().height());

    cell_height_ = grid_view->frameSize().height();
    cell_width_ = grid_view->frameSize().width();



    srand(time(0));
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            game * item = new game(j,i,cell_width_/20, cell_height_/10);
            cells[i][j] = item;
            MakeBoard_->addItem(item);
           // connect(item, &game::increase, this, &MainWindow::receive_inc);
           // connect(item, &game::decrease, this, &MainWindow::receive_dec);

            if(item->get_color() == QColor(240,20,120))
            {
                PopulationCounter(1);
            }
        }
    }
    ui->label->setText(QString("Turn#: ")+QString::number(turnCounter_));
    ui->label_2->setText(QString("Population: ")+QString::number(population_) + QString(" (") + QString::number((population_ * 100)/200) +QString("%" ));


//    MakePopGraph_ = new QGraphicsScene;
//    QGraphicsView *graph_view = ui->MainPlot_2;
//    graph_view->setScene(MakePopGraph_);
//    graph_view->setSceneRect(0,0,graph_view->frameSize().width(), graph_view->frameSize().height());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PopulationCounter(int pop)
{
    population_ += pop;
    ui->label_2->setText(QString("Population: ")+QString::number(population_)+QString(" ") +QString::number((population_ * 100)/200)+QString("%"));

}

void MainWindow::turnCount() //handles number of turns
{
    turnCounter_++; //increment turn counter
   // ui->label->setText(QString("Turn#: ")+QString::number(turnCounter_)); //print number turn
}

void MainWindow::checkAlive() //determine if cells should be dead or alive
{

}



//bool MainWindow::is_alive() //checks if cells are alive
//{

//}



//void MainWindow::on_restartButton_click() //button for restarting game
//{

//}


//void MainWindow::on_playButton_click() //button for starting game
//{

//}

//void MainWindow::on_pauseButton_click()
//{
//    timer->stop();
//}

//void MainWindow::on_stepButton_click()
//{
    //checkAlive();
//}


