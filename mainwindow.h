#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataCollector.h"
#include <QPushButton>
#include <QVector>
#include <vector>
#include "defines.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void plot(uint8_t plotNumber, vector<double> xData, vector<double> yData);

private slots:
    void on_sensorButton0_clicked();

    void on_sensorButton1_clicked();

    void on_sensorButton2_clicked();

    void on_sensorButton3_clicked();

private:
    Ui::MainWindow *ui;
    DataCollector controller;
};
#endif // MAINWINDOW_H
