//
// CONFIGURATION CAN BE SET IN defines.h
//

#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include "defines.h"



struct SensorData{
    double A;
    double freq;
};

class Config{
public:
    void operator=(const Config &) = delete;
    Config(Config &other) = delete;


    static Config* getInstance();
    void initialise();

public:
    std::vector<SensorData> sensorsData;
    double stddev;
private:
    Config(){}
    //static Config* _config={};
};

#endif // CONFIG_H
