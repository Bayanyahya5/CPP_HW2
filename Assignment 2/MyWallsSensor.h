#ifndef MY_WALLS_SENSOR_H
#define MY_WALLS_SENSOR_H

#include "wall_sensor.h"

class MyWallsSensor : public WallsSensor {
public:
    bool isWall(Direction d) const override;
};

#endif // MY_WALLS_SENSOR_H
