#ifndef MY_WALLS_SENSOR_H
#define MY_WALLS_SENSOR_H

#include "wall_sensor.h"
#include <vector>

class MyWall_sensor : public WallsSensor {
public:
    MyWall_sensor(const std::vector<std::vector<char>>& house, int row, int col);
    bool isWall(Direction d) const override;
    void setPosition(int row, int col);

private:
    const std::vector<std::vector<char>>& house_;
    int row_;
    int col_;
};

#endif // MY_WALLS_SENSOR_H