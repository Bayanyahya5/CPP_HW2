#ifndef WALL_SENSOR_H_
#define WALL_SENSOR_H_

#include "enums.h"

/**
 * @class WallsSensor
 * @brief An abstract class representing the walls sensor for the vacuum cleaner.
 */
class WallsSensor
{
public:
	virtual ~WallsSensor() {}

    /**
     * @brief Check if there is a wall in the given direction.
     * @param d The direction to check.
     * @return True if there is a wall, false otherwise.
     */
	virtual bool isWall(Direction d) const = 0;
};

#endif // WALL_SENSOR_H_
