#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include <vector>
#include <future>
#include <windows.h>
#include <random>
#include <ctime>
#include <cmath>
#include "config.h"
#include "defines.h"
#include "utils.h"

using namespace std;

using VibrationData = vector<double>;

class MainWindow;

class Sensor {
public:
    Sensor(uint8_t number, double _A, double _freq);

    VibrationData getData(const double& deltaTime, const double& stddev) const;
    bool IsWathed() const;
    volatile bool& IsWathed();
private:
    VibrationData generateData(const double& deltaTime, const double& stddev) const;
    uint8_t _number;
    double A; //amplitude
    double freq; // frequency
    volatile bool isWatched;
};

class DataCollector {
public:
    DataCollector();
    void CollectData(uint8_t sensorNumber);
    void stopSensor(uint8_t sensorNumber);
    void setParentUI(MainWindow* ui);
private:
    void CollectDataSingleThreadTest(uint8_t sensorNumber);

    std::vector<Sensor> sensors;
    Config* config;
    std::vector<std::future<void>> futures;
    MainWindow* parentUI;
    std::vector<std::vector<double>> vibrationData;
    std::vector<std::vector<double>> timeData;
    std::mutex data_collector_mutex;
};

#endif // DATACOLLECTOR_H
