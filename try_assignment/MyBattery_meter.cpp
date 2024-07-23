#include "MyBattery_meter.h"

MyBattery_meter::MyBattery_meter(std::size_t maxBattery)
    : batteryState_(maxBattery), maxBattery_(maxBattery) {}

std::size_t MyBattery_meter::getBatteryState() const
{
    return batteryState_; /////////////////////////// batteryState is double but the return value is size t, check if need to change to return std::size_t(batteryState_)
}

void MyBattery_meter::decreaseBattery()
{
    if (batteryState_ > 0)
    {
        batteryState_--;
    }
}

void MyBattery_meter::chargeBattery()
{
    batteryState_ += maxBattery_ / 20;
    if (batteryState_ > maxBattery_)
    {
        batteryState_ = maxBattery_;
    }
}
