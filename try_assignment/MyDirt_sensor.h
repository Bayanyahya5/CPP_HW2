#ifndef MY_DIRT_SENSOR_H
#define MY_DIRT_SENSOR_H

#include "dirt_sensor.h"
#include <vector>

/**
 * @class MyDirt_sensor
 * @brief A concrete implementation of the DirtSensor class.
 */
class MyDirt_sensor : public DirtSensor
{
public:
    MyDirt_sensor(std::vector<std::vector<int>> &dirtLevels, int row, int col);
    int dirtLevel() const override;

    /**
     * @brief Set the position of the dirt sensor.
     * @param row The current row.
     * @param col The current column.
     */
    void setPosition(int row, int col);

    /**
     * @brief Get the total amount of dirt left in the house.
     * @return The total dirt level.
     */
    int houseDirtLevel() const;

    /**
     * @brief Clean the current position.
     */
    void cleen();

private:
    std::vector<std::vector<int>> &dirtLevels_;
    int row_;
    int col_;
};

#endif // MY_DIRT_SENSOR_H