#ifndef MY_BATTERY_METER_H
#define MY_BATTERY_METER_H

#include "battery_meter.h"

class MyBatteryMeter : public BatteryMeter {
private://///////////////////////
    std::size_t BatteryMeter;/////////////////////////////////

public:
    std::size_t getBatteryState() const override;
};

#endif // MY_BATTERY_METER_H
