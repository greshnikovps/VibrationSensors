#include "dataCollector.h"
#include "mainwindow.h"
#include <QDebug>
using namespace std;

using VibrationData = vector<double>;


    Sensor::Sensor(uint8_t number, double _A, double _freq)
        : _number(number)
        , A(_A)
        , freq(_freq)
        , isWatched(false)
    {

    };

    VibrationData Sensor::getData(const double& deltaTime, const double& stddev) const {
        return generateData(deltaTime, stddev);
	}
    bool Sensor::IsWathed() const {
		return isWatched;
	}
    volatile bool& Sensor::IsWathed(){
        return isWatched;
    }

    VibrationData Sensor::generateData(const double& deltaTime, const double& stddev) const {
        VibrationData result(DATA_LENGTH);
		std::default_random_engine generator(42);
		std::normal_distribution<double> distribution(0.0, stddev);
		auto now = std::chrono::system_clock::now().time_since_epoch().count();
        now = now % 100000000000;
		for (size_t i = 1; i <= DATA_LENGTH; ++i) {
            result[DATA_LENGTH - i] = A * sin(freq * (now / 10000000. - deltaTime *(i-1)))
				+ distribution(generator);
		}
		return result;
	}

    DataCollector::DataCollector(): config(Config::getInstance()) {
        config->initialise();
        sensors = { {0, config->sensorsData[0].A, config->sensorsData[0].freq},
            {1, config->sensorsData[1].A, config->sensorsData[1].freq},
            {2, config->sensorsData[2].A, config->sensorsData[2].freq},
            {3, config->sensorsData[3].A, config->sensorsData[3].freq}
        };
        vibrationData.resize(4);
        timeData.resize(4);
        futures.resize(4);
        //data.resize(4);
    }

//    void CollectDataSingleThread(DataCollector& c, uint8_t sensorNumber) {
//        c.data_collector_mutex.lock();
//        c.sensors[sensorNumber].IsWathed() = true;
//        c.data_collector_mutex.unlock();

//        double processedData;
//        double deltaTime = SENSOR_TIMEFRAME / 1000. / DATA_LENGTH;

//        while (c.sensors[sensorNumber].IsWathed()) {
//            Sleep(SENSOR_TIMEFRAME); // immitating that sensor send data every SENSOR_TIMEFRAME miliseconds
//            c.data_collector_mutex.lock();
//            processedData = MSV(c.sensors[sensorNumber].getData(deltaTime, c.config.stddev));
//            if (c.vibrationData[sensorNumber].size() >= MAX_QT_PLOT_CAPACITY){
//                c.vibrationData[sensorNumber].clear();
//                c.timeData[sensorNumber].clear();
//            }
//            c.vibrationData[sensorNumber].push_back(processedData);
//            if (!c.timeData[sensorNumber].empty()) {
//                c.timeData[sensorNumber].push_back(c.timeData[sensorNumber].back() + SENSOR_TIMEFRAME / 1000.);
//            } else {
//                c.timeData[sensorNumber].push_back(0);
//            }
//            c.parentUI->plot(sensorNumber, c.vibrationData[sensorNumber], c.timeData[sensorNumber]);
//            c.data_collector_mutex.unlock();
//        }
//        return;
//    }
    void DataCollector::CollectDataSingleThreadTest(uint8_t sensorNumber){
        data_collector_mutex.lock();
        sensors[sensorNumber].IsWathed() = true;
        data_collector_mutex.unlock();

        double processedData;
        double deltaTime = SENSOR_TIMEFRAME / 1000. / DATA_LENGTH;

        while (sensors[sensorNumber].IsWathed()) {
            Sleep(SENSOR_TIMEFRAME); // immitating that sensor send data every SENSOR_TIMEFRAME miliseconds
            data_collector_mutex.lock();
            processedData = MSV(sensors[sensorNumber].getData(deltaTime, config->stddev));
            if (vibrationData[sensorNumber].size() >= MAX_QT_PLOT_CAPACITY){
                vibrationData[sensorNumber].clear();
                timeData[sensorNumber].clear();
            }
            vibrationData[sensorNumber].push_back(processedData);
            if (!timeData[sensorNumber].empty()) {
                timeData[sensorNumber].push_back(timeData[sensorNumber].back() + SENSOR_TIMEFRAME / 1000.);
            } else {
                timeData[sensorNumber].push_back(0);
            }
            parentUI->plot(sensorNumber, vibrationData[sensorNumber], timeData[sensorNumber]);
            data_collector_mutex.unlock();
        }
        return;
    }

    void DataCollector::CollectData(uint8_t sensorNumber)  {
        futures[sensorNumber] = async(&DataCollector::CollectDataSingleThreadTest, ref(*this), sensorNumber);
    }

    void DataCollector::stopSensor(uint8_t sensorNumber){
        sensors[sensorNumber].IsWathed() = false;
    }

    void DataCollector::setParentUI(MainWindow* ui) {
        parentUI = ui;
    }
