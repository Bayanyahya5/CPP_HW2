#ifndef MYSIMULATOR_H
#define MYSIMULATOR_H

#include <string>
#include <vector>
#include "MyAlgorithm.h"
#include "wall_sensor.h"
#include "dirt_sensor.h"
#include "battery_meter.h"

class MySimulator {
public:
    void readHouseFile(const std::string& houseFilePath);
    void setAlgorithm(MyAlgorithm& algorithm);
    void run();

private:
    std::string houseName;
    std::size_t maxSteps;
    std::size_t maxBattery;
    std::size_t rows;
    std::size_t cols;
    std::vector<std::vector<char>> house;
    MyAlgorithm* algo;

    bool atDockingStation() const;
};

#endif // MYSIMULATOR_H
