#ifndef ROBOT_ALGORITHM_H__
#define ROBOT_ALGORITHM_H__


#include <cstddef>

#include "enums.h"
#include "battery_meter.h"
#include "wall_sensor.h"
#include "dirt_sensor.h"

/**
 * @class AbstractAlgorithm
 * @brief An abstract class representing the algorithm for controlling the vacuum cleaner.
 */
class AbstractAlgorithm {
public:
	virtual ~AbstractAlgorithm() {}

	/**
     * @brief Set the maximum number of steps the algorithm is allowed to take.
     * @param maxSteps The maximum number of steps.
     */
	virtual void setMaxSteps(std::size_t maxSteps) = 0;

    /**
     * @brief Set the walls sensor.
     * @param sensor The walls sensor.
     */
	virtual void setWallsSensor(const WallsSensor&) = 0;

    /**
     * @brief Set the dirt sensor.
     * @param sensor The dirt sensor.
     */
	virtual void setDirtSensor(const DirtSensor&) = 0;

    /**
     * @brief Set the battery meter.
     * @param meter The battery meter.
     */
	virtual void setBatteryMeter(const BatteryMeter&) = 0;

    /**
     * @brief Determine the next step for the vacuum cleaner.
     * @return The next step.
     */
	virtual Step nextStep() = 0;
};

#endif  // ROBOT_ALGORITHM_H__
