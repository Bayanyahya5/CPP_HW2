#include "MyAlgorithm.h"

void MyAlgorithm::setMaxSteps(std::size_t maxSteps) {
    maxSteps_ = maxSteps;
    currentSteps_ = 0;
}

void MyAlgorithm::setWallsSensor(const WallsSensor& sensor) {
    wallsSensor_ = &sensor;
}

void MyAlgorithm::setDirtSensor(const DirtSensor& sensor) {
    dirtSensor_ = &sensor;
}

void MyAlgorithm::setBatteryMeter(const BatteryMeter& meter) {
    batteryMeter_ = &meter;
}

Step MyAlgorithm::nextStep() {
    if (currentSteps_ >= maxSteps_) { //|| batteryMeter_ >= maxBattery_ check thissssssssssssssssssss
        return Step::Finish;
    }

    // Implement the cleaning logic
}
