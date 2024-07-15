#include "MySimulator.h"
#include "MyWallsSensor.h"
#include "MyDirtSensor.h"
#include "MyBatteryMeter.h"
#include <fstream>
#include <iostream>
#include <limits>

void MySimulator::readHouseFile(const std::string& houseFilePath) {
    std::ifstream file(houseFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open house file.\n";
        return;
    }

    std::string line;
    getline(file, houseName);
    file >> line >> line >> maxSteps;
    file >> line >> line >> maxBattery;
    file >> line >> line >> rows;
    file >> line >> line >> cols;

    house.resize(rows);
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore remaining part of the line
    for (std::size_t i = 0; i < rows; ++i) {
        getline(file, house[i]);
    }

    file.close();
}

void MySimulator::setAlgorithm(MyAlgorithm& algorithm) {
    algo = &algorithm;
    algo->setMaxSteps(maxSteps);
    MyWallsSensor wallsSensor;
    MyDirtSensor dirtSensor;
    MyBatteryMeter batteryMeter;
    algo->setWallsSensor(wallsSensor);
    algo->setDirtSensor(dirtSensor);
    algo->setBatteryMeter(batteryMeter);
}

void MySimulator::run() {
    // Implement the simulation logic
}
