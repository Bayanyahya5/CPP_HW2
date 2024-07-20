#ifndef MYSIMULATOR_H
#define MYSIMULATOR_H

#include <string>
#include <vector>
#include <memory>
#include "abstract_algorithm.h"
#include "MyWall_sensor.h"
#include "MyDirt_sensor.h"
#include "MyBattery_meter.h"
#include "MyAlgorithm.h"

class MySimulator {
public:
    void readHouseFile(const std::string& houseFilePath);
    void setAlgorithm(AbstractAlgorithm& algo);
    void run();

private:
    std::vector<std::vector<char>> house_;
    std::vector<std::vector<int>> dirtLevels_;
    std::unique_ptr<MyWall_sensor> wallsSensor_;
    std::unique_ptr<MyDirt_sensor> dirtSensor_;
    std::unique_ptr<MyBattery_meter> batteryMeter_;
    std::size_t maxSteps_;
    std::size_t maxBattery_;
    int dockingRow_;
    int dockingCol_;
    int currentRow_;
    int currentCol_;
    std::size_t currentStep_;
    std::vector<char> steps_;

    void updateSensors();
};

#endif // MYSIMULATOR_H