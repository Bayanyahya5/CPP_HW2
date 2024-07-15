#include "MyAlgorithm.h"

void MyAlgorithm::setMaxSteps(std::size_t maxSteps) {
    this->maxSteps = maxSteps;
}

void MyAlgorithm::setWallsSensor(const WallsSensor& wallsSensor) {
    this->wallsSensor = &wallsSensor;
}

void MyAlgorithm::setDirtSensor(const DirtSensor& dirtSensor) {
    this->dirtSensor = &dirtSensor;
}

void MyAlgorithm::setBatteryMeter(const BatteryMeter& batteryMeter) {
    this->batteryMeter = &batteryMeter;
}

Step MyAlgorithm::nextStep() {
    // Implementation of algorithm to decide next step
    // For now, returning Stay as a placeholder
    return Step::Stay;
}
