#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "iio_data.h"
#include <deque>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getDataInBuffer();
    void calculateRP();
    void getAverageData();

private slots:
    void start_stop();
    void animation();

private:
    int buffer_count = 15;
    Ui::MainWindow *ui;
    Iio_data *iio_data;
    QTimer *timer;
    bool anim_play;
    double x,y,z,temp;
    double roll, pitch;
    double roll_average, pitch_average;
    std::deque<double> roll_que;
    std::deque<double> pitch_que;


};
#endif // MAINWINDOW_H
