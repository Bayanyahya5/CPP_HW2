#ifndef MY_ALGORITHM_H
#define MY_ALGORITHM_H

#include "abstract_algorithm.h"
#include "wall_sensor.h"
#include "dirt_sensor.h"
#include "battery_meter.h"

class MyAlgorithm : public AbstractAlgorithm {
    std::size_t maxSteps;
    const WallsSensor* wallsSensor;
    const DirtSensor* dirtSensor;
    const BatteryMeter* batteryMeter;

public:
    void setMaxSteps(std::size_t maxSteps) override;
    void setWallsSensor(const WallsSensor& wallsSensor) override;
    void setDirtSensor(const DirtSensor& dirtSensor) override;
    void setBatteryMeter(const BatteryMeter& batteryMeter) override;
    Step nextStep() override;
};

#endif // MY_ALGORITHM_H
