#include "config.h"

Config* Config::getInstance(){
    static Config instance;
    return &instance;
}

void Config::initialise(){
    sensorsData = {
        {SENSOR0_A, SENSOR0_freq},
        {SENSOR1_A, SENSOR1_freq},
        {SENSOR2_A, SENSOR2_freq},
        {SENSOR3_A, SENSOR3_freq}
    };
    stddev = STDDEV;
}
