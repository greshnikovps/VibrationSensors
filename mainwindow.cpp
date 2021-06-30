#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qcustomplot.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot0->addGraph();
    ui->plot0->xAxis->setRange(0, 10);
    ui->plot0->yAxis->setRange(-STDDEV, SENSOR0_A+STDDEV);

    ui->plot1->addGraph();
    ui->plot1->xAxis->setRange(0, 10);
    ui->plot1->yAxis->setRange(-STDDEV, SENSOR1_A+STDDEV);

    ui->plot2->addGraph();
    ui->plot2->xAxis->setRange(0, 10);
    ui->plot2->yAxis->setRange(-STDDEV, SENSOR2_A+STDDEV);

    ui->plot3->addGraph();
    ui->plot3->xAxis->setRange(0, 10);
    ui->plot3->yAxis->setRange(-STDDEV, SENSOR3_A+STDDEV);

    controller.setParentUI(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot(uint8_t plotNumber, vector<double> xData, vector<double> yData){
    QVector<double> QxData = QVector<double>(xData.begin(), xData.end());
    QVector<double> QyData = QVector<double>(yData.begin(), yData.end());

    switch(plotNumber){
    case 0:
        ui->plot0->graph()->setData(QyData, QxData);
        ui->plot0->replot();
        ui->plot0->update();
        break;

    case 1:
        ui->plot1->graph()->setData(QyData, QxData);
        ui->plot1->replot();
        ui->plot1->update();
        break;

    case 2:
        ui->plot2->graph()->setData(QyData, QxData);
        ui->plot2->replot();
        ui->plot2->update();
        break;

    case 3:
        ui->plot3->graph()->setData(QyData, QxData);
        ui->plot3->replot();
        ui->plot3->update();
        break;
    }
}

void MainWindow::on_sensorButton0_clicked()
{
    if (ui->sensorButton0->isChecked()){
        controller.CollectData(0);
    } else {
        controller.stopSensor(0);
    }
}

void MainWindow::on_sensorButton1_clicked()
{
    if (ui->sensorButton1->isChecked()){
        controller.CollectData(1);
    } else {
        controller.stopSensor(1);
    }
}

void MainWindow::on_sensorButton2_clicked()
{
    if (ui->sensorButton2->isChecked()){
        controller.CollectData(2);
    } else {
        controller.stopSensor(2);
    }
}

void MainWindow::on_sensorButton3_clicked()
{
    if (ui->sensorButton3->isChecked()){
        controller.CollectData(3);
    } else {
        controller.stopSensor(3);
    }
}
