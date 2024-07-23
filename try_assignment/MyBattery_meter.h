#ifndef MY_BATTERY_METER_H
#define MY_BATTERY_METER_H

#include "battery_meter.h"

/**
 * @class MyBattery_meter
 * @brief A concrete implementation of the BatteryMeter class.
 */
class MyBattery_meter : public BatteryMeter
{
public:
    MyBattery_meter(std::size_t maxBattery);
    std::size_t getBatteryState() const override;

    /**
     * @brief Decrease the battery state by one step.
     */
    void decreaseBattery();

    /**
     * @brief Charge the battery.
     */
    void chargeBattery();

private:
    std::size_t batteryState_;
    std::size_t maxBattery_;
};

#endif // MY_BATTERY_METER_H