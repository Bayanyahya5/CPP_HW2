#ifndef DIRT_SENSOR_H_
#define DIRT_SENSOR_H_

/**
 * @class DirtSensor
 * @brief An abstract class representing the dirt sensor for the vacuum cleaner.
 */
class DirtSensor {
public:
	virtual ~DirtSensor() {}

    /**
     * @brief Get the current dirt level.
     * @return The current dirt level.
     */
	virtual int dirtLevel() const = 0;
};

#endif  // DIRT_SENSOR_H_
