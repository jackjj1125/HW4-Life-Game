#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QtWidgets>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set up timer and set start flag to false
    initTimer();
    start_ = false;
    population_ = 0;
    turnCounter_ = 0;

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
            cells[i][j]->set_nextStatus(-1);
            MakeBoard_->addItem(item);
            connect(item, &game::reviveCell, this, &MainWindow::clickCellSlot);
            connect(item, &game::killCell, this, &MainWindow::clickCellSlot);

            if(item->get_status())
            {
                increasePopulation();
            }
        }
    }
    ui->label->setText(QString("Turn: ")+QString::number(turnCounter_));
    ui->label_2->setText(QString("Population: ")+QString::number(population_) + QString(" (") + QString::number((population_ * 100)/200) +QString("%" ));
    //ui->label_2->setText(QString("Population: ")+QString::number(population_));




    connect(ui->playButton, &QAbstractButton::pressed, this, &MainWindow::on_playButton_click);
    connect(ui->pauseButton, &QAbstractButton::pressed, this, &MainWindow::on_pauseButton_click);
    connect(ui->stepButton, &QAbstractButton::pressed, this, &MainWindow::on_stepButton_click);
    connect(ui->speedSlider, &QAbstractSlider::sliderMoved, this, &MainWindow::speedSliderMoved);
    connect(ui->restartButton, &QAbstractButton::pressed, this, &MainWindow::on_restartButton_click);


    MakePopGraph_ = new QGraphicsScene; //making new graph for pop
    QGraphicsView * graph_view = ui->graphGraphicsView; //putting it on the ui
    graph_view->setScene(MakePopGraph_); //set scene for graph
    graph_view->setSceneRect(0,0,graph_view->frameSize().width(), graph_view->frameSize().height()); //set scene for bar rectangles

    double pop_percent = (double(population_) / 200.0); //population as a percent
    y_bar = graph_view->frameSize().height() -2; //y value on bar
    h_bar = graph_view->frameSize().height(); //height is population as percent
    Bar* first_bar = new Bar(0,y_bar, int(pop_percent * h_bar)); //making new bar(the first one)
    popBar_.push_back(first_bar); //pushing it onto vector
    MakePopGraph_->addItem(first_bar); //adding it to ui

    connect(ui->playButton, &QAbstractButton::pressed, this, &MainWindow::on_playButton_click);
    connect(ui->pauseButton, &QAbstractButton::pressed, this, &MainWindow::on_pauseButton_click);
    connect(ui->stepButton, &QAbstractButton::pressed, this, &MainWindow::on_stepButton_click);
    connect(ui->speedSlider, &QAbstractSlider::sliderMoved, this, &MainWindow::speedSliderMoved);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initTimer(){
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_stepButton_click()));
}

void MainWindow::changeInterval(int t){
    if(t < 2){
        return;
    }

    timer->setInterval(1000 / t);
}

void MainWindow::increasePopulation(){
    population_++;
    ui->label_2->setText(QString("Population: ")+QString::number(population_)+QString(" ") +QString::number((population_ * 100)/200)+QString("%"));

}
void MainWindow::decreasePopulation(){
    population_--;
    ui->label_2->setText(QString("Population: ")+QString::number(population_)+QString(" ") +QString::number((population_ * 100)/200)+QString("%"));

}

void MainWindow::turnCount() //handles number of turns
{
    turnCounter_++; //increment turn counter
    ui->label->setText(QString("Turn#: ")+QString::number(turnCounter_)); //print number turn
}

std::vector<game*> MainWindow::getNeighbors(int i, int j){
    std::vector<game*> neighbors;

    if(i == 0 && j == 0){  // top left corner
        neighbors.push_back(cells[9][19]);
        neighbors.push_back(cells[9][j]);
        neighbors.push_back(cells[9][j+1]);

        neighbors.push_back(cells[i][19]);
        neighbors.push_back(cells[i][j+1]);

        neighbors.push_back(cells[i+1][19]);
        neighbors.push_back(cells[i+1][j]);
        neighbors.push_back(cells[i+1][j+1]);

        return neighbors;
    }
    else if(i == 9 && j == 19){ // bottom right corner
        neighbors.push_back(cells[i-1][j-1]);
        neighbors.push_back(cells[i-1][j]);
        neighbors.push_back(cells[i-1][0]);

        neighbors.push_back(cells[i][j-1]);
        neighbors.push_back(cells[i][0]);

        neighbors.push_back(cells[0][j-1]);
        neighbors.push_back(cells[0][j]);
        neighbors.push_back(cells[0][0]);

        return neighbors;
    }
    else if(i == 0 && j == 19){ // top right corner
        neighbors.push_back(cells[9][j-1]);
        neighbors.push_back(cells[9][j]);
        neighbors.push_back(cells[9][19]);

        neighbors.push_back(cells[i][j-1]);
        neighbors.push_back(cells[i][0]);

        neighbors.push_back(cells[i+1][j-1]);
        neighbors.push_back(cells[i+1][j]);
        neighbors.push_back(cells[i+1][0]);

        return neighbors;
    }
    else if(i == 9 && j == 0){ // bottom left corner
        neighbors.push_back(cells[i-1][19]);
        neighbors.push_back(cells[i-1][j]);
        neighbors.push_back(cells[i-1][j+1]);

        neighbors.push_back(cells[i][19]);
        neighbors.push_back(cells[i][j+1]);

        neighbors.push_back(cells[0][19]);
        neighbors.push_back(cells[0][j]);
        neighbors.push_back(cells[0][j+1]);

        return neighbors;
    }
    else if(i == 0 && j != 0 && j != 19){  // top row, no corners
        neighbors.push_back(cells[9][j-1]);
        neighbors.push_back(cells[9][j]);
        neighbors.push_back(cells[9][j+1]);

        neighbors.push_back(cells[i][j-1]);
        neighbors.push_back(cells[i][j+1]);

        neighbors.push_back(cells[i+1][j-1]);
        neighbors.push_back(cells[i+1][j]);
        neighbors.push_back(cells[i+1][j+1]);

        return neighbors;
    }
    else if(i != 0 && i != 9 && j == 0){ // far right column, no corners
        neighbors.push_back(cells[i-1][19]);
        neighbors.push_back(cells[i-1][j]);
        neighbors.push_back(cells[i-1][j+1]);

        neighbors.push_back(cells[i][19]);
        neighbors.push_back(cells[i][j+1]);

        neighbors.push_back(cells[i+1][19]);
        neighbors.push_back(cells[i+1][j]);
        neighbors.push_back(cells[i+1][j+1]);

        return neighbors;
    }
    else if(i == 9 && j != 19 && j != 0){ // bottom row, no corners
        neighbors.push_back(cells[i-1][j-1]);
        neighbors.push_back(cells[i-1][j]);
        neighbors.push_back(cells[i-1][j+1]);

        neighbors.push_back(cells[i][j-1]);
        neighbors.push_back(cells[i][j+1]);

        neighbors.push_back(cells[0][j-1]);
        neighbors.push_back(cells[0][j]);
        neighbors.push_back(cells[0][j+1]);

        return neighbors;
    }
    else if(i != 0 && i != 9 && j == 19){ // far left column, no corners
        neighbors.push_back(cells[i-1][j-1]);
        neighbors.push_back(cells[i-1][j]);
        neighbors.push_back(cells[i-1][0]);

        neighbors.push_back(cells[i][j-1]);
        neighbors.push_back(cells[i][0]);

        neighbors.push_back(cells[i+1][j-1]);
        neighbors.push_back(cells[i+1][j]);
        neighbors.push_back(cells[i+1][0]);

        return neighbors;
    }
    else{ // no edges or corners
        neighbors.push_back(cells[i-1][j-1]);
        neighbors.push_back(cells[i-1][j]);
        neighbors.push_back(cells[i-1][j+1]);

        neighbors.push_back(cells[i][j-1]);
        neighbors.push_back(cells[i][j+1]);

        neighbors.push_back(cells[i+1][j-1]);
        neighbors.push_back(cells[i+1][j]);
        neighbors.push_back(cells[i+1][j+1]);
    }

    return neighbors;
}

int MainWindow::checkNeighbors(std::vector<game*> neighbors){
    int aliveCount = 0;

    for(int i = 0; i < neighbors.size(); i++){
        if(neighbors[i]->get_status()){
            aliveCount++;
        }
    }

    if(aliveCount < 2){
        return 1;
    }
    if(aliveCount == 2){
        return 2;
    }
    if(aliveCount > 3){
        return 3;
    }
    if(aliveCount == 3){
        return 4;
    }

}

void MainWindow::checkAlive() //determine if cells should be dead or alive
{
    //qDebug() << "checking if cells are dead or alive";


    int status = 0;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20; j++){
            status = checkNeighbors(getNeighbors(i, j));

            if(cells[i][j]->get_status()){
                if(status == 1 || status == 3){
                    // kill cell
                    cells[i][j]->set_nextStatus(0);
                }
                // if status == 2, do nothing
            }
            else{
                if(status == 4){
                    // make cell alive
                    cells[i][j]->set_nextStatus(1);
                }
            }
        }
    }
    qDebug() << "next status set";
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20; j++){
            if(cells[i][j]->get_nextStatus() == 1){
                cells[i][j]->revive();
            }
            else if(cells[i][j]->get_nextStatus() == 0){
                cells[i][j]->kill();
            }
            cells[i][j]->set_nextStatus(-1);
        }
    }
    MakePopGraph_->update(); //update our graph for population every time we update cells
    if(popBar_.size() > 20) //start moving to the left as graph keeps going
    {
        int prev = 0; //prev bar
        for(Bar* bar : popBar_) //for the graph
        {
            bar->set_x(-1 * bar->get_width()); //x is our width
            prev = bar->get_x(); //set prev to x
        }
        double pop_percent = (double(population_) / 200.0); //population as a percent for our graph
        Bar* bar = new Bar(prev + 30, y_bar, int(pop_percent * h_bar)); //making a new bar with x + 30
        popBar_.push_back(bar); //pushing our bar onto vector
        MakePopGraph_->addItem(bar); //adding it to the UI
    }
    else //not moving to the left
    {
        double pop_percent = (double(population_) / 200.0); //population as a percent
        Bar* bar = new Bar((turnCounter_ * 30) + 30, y_bar, int(pop_percent * h_bar)); //making new bar with num turns as x
        popBar_.push_back(bar); //pushing bar onto vector
        MakePopGraph_->addItem(bar); //adding it to the ui
    }
}

void MainWindow::clickCellSlot(game * cell){
    if(cell->get_status()){
        increasePopulation();
    }
    else{
        decreasePopulation();
    }
}


void MainWindow::on_restartButton_click() //button for restarting game
{
    qDebug() << "Restart Game Button Clicked";
    if(start_)
    {
        initTimer();
        timer->start();
    }
}

//button for starting game
void MainWindow::on_playButton_click(){
    qDebug() << "Play button clicked!";

    if(!start_){
        timer->start();
        start_ = true;
    }
}

void MainWindow::on_pauseButton_click(){
    qDebug() << "Pause button clicked!";
    if(start_){
        timer->stop();
        start_ = false;
    }
}

void MainWindow::on_stepButton_click(){
    //qDebug() << "Step button clicked!";
    checkAlive();
    turnCount();
}

void MainWindow::speedSliderMoved(int position){
    if(position < 2){
        ui->speedLabel->setText(QString("Speed: 1 sec"));
    }
    else{
        changeInterval(position);
        ui->speedLabel->setText(QString("Speed: ")+QString::number(1000 / position)+QString(" ms"));
    }
}
