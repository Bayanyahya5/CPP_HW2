#ifndef MY_DIRT_SENSOR_H
#define MY_DIRT_SENSOR_H

#include "dirt_sensor.h"
#include <vector>

class MyDirt_sensor : public DirtSensor {
public:
    MyDirt_sensor(const std::vector<std::vector<int>>& dirtLevels, int row, int col);
    int dirtLevel() const override;
    void setPosition(int row, int col);

private:
    const std::vector<std::vector<int>>& dirtLevels_;
    int row_;
    int col_;
};

#endif // MY_DIRT_SENSOR_H