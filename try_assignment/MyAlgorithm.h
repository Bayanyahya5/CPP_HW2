#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include "abstract_algorithm.h"
#include "MyWall_sensor.h"
#include "MyDirt_sensor.h"
#include "MyBattery_meter.h"

class MyAlgorithm : public AbstractAlgorithm {
public:
    void setMaxSteps(std::size_t maxSteps) override;
    void setWallsSensor(const WallsSensor&) override;
    void setDirtSensor(const DirtSensor&) override;
    void setBatteryMeter(const BatteryMeter&) override;
    Step nextStep() override;

private:
    const WallsSensor* wallsSensor_;
    const DirtSensor* dirtSensor_;
    const BatteryMeter* batteryMeter_;
    std::size_t maxSteps_;
    std::size_t currentSteps_;
};

#endif // MYALGORITHM_H