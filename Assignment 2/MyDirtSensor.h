#ifndef MY_DIRT_SENSOR_H
#define MY_DIRT_SENSOR_H

#include <string>//////////////////////////
#include <vector>///////////////////////
#include "dirt_sensor.h"

class MyDirtSensor : public DirtSensor {
private:////////////////////////
    std::vector<char> house;/////////////////////////

public:
    int dirtLevel() const override;
};

#endif // MY_DIRT_SENSOR_H
