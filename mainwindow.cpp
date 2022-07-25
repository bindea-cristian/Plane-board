#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>
#include <QTimer>
#include "qdebug.h"

// https://github.com/marek-cel/QFlightinstruments

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    iio_data = new Iio_data();
    timer = new QTimer(this);

    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::start_stop);
    connect(timer, SIGNAL(timeout()),this,SLOT(animation()));

    timer->start(10);
    anim_play = true;

    getDataInBuffer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_stop(){

    if(anim_play)
    {
        ui->pushButton->setText("Start");
        if(!roll_que.empty())
            roll_que.clear();
        if(!pitch_que.empty())
            pitch_que.clear();
    }
    else
    {
        ui->pushButton->setText("Stop");
        getDataInBuffer();
    }

    anim_play = ! anim_play;
}

void MainWindow::animation(){
    if(anim_play)
    {
        getAverageData();

        QString labelText = "Sensor temperature: " +  QString::number(temp);
        ui->label->setText(labelText);

        ui->graphicsView->setPitch(pitch_average);
        ui->graphicsView->setRoll(roll_average);

        ui->graphicsView->redraw();
    }
}


void MainWindow::getDataInBuffer(){
    for(int i=0;i<buffer_count;i++)
    {
        iio_data->getData(x,y,z,temp);
        calculateRP();
        roll_que.push_back(roll);
        pitch_que.push_back(pitch);
    }
}

void MainWindow::calculateRP(){
    int sign = z>0 ? 1 : -1;

    roll  = atan2( y,   sign *  sqrt(z*z + x*x));
    pitch = asin( x / sqrt( pow(x,2) + pow(y,2) + pow(z,2) ));

    pitch = pitch * (180.0/M_PI);
    roll = roll * (180.0/M_PI) ;
}

void MainWindow::getAverageData(){
    iio_data->getData(x,y,z,temp);
    calculateRP();

    roll_average = 0;
    roll_que.pop_front();
    roll_que.push_back(roll);

    pitch_average = 0;
    pitch_que.pop_front();
    pitch_que.push_back(pitch);

    for(double i:roll_que)
        roll_average+=i;
    roll_average/=buffer_count;

    for(double i:pitch_que)
        pitch_average+=i;
    pitch_average/=buffer_count;
}
