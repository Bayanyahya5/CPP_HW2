#include "MySimulator.h"
#include "MyWallsSensor.h"
#include "MyDirtSensor.h"
#include "MyBatteryMeter.h"
#include <fstream>
#include <iostream>
#include <limits>

void MySimulator::readHouseFile(const std::string& houseFilePath) 
{
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

    house.resize(rows, std::vector<char>(cols, ' '));
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore remaining part of the line
    for (std::size_t i = 0; i < rows; ++i) {
        getline(file, line);
        for (std::size_t j = 0; j < cols && j < line.length(); ++j) {
            house[i][j] = line[j];
        }
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
    std::size_t currentSteps = 0;
    std::size_t currentBattery = maxBattery;

    while (currentSteps < maxSteps) {
        Step step = algo->nextStep();
        if (step == Step::Finish) {
            std::cout << "Simulation finished successfully.\n";
            return;
        }

        // Handle step execution, dirt cleaning, and battery management
        switch (step) {
            case Step::North: 
                // Move north
                break;
            case Step::East: 
                // Move east
                break;
            case Step::South: 
                // Move south
                break;
            case Step::West: 
                // Move west
                break;
            case Step::Stay: 
                // Stay and clean
                break;
            default: 
                break;
        }

        if (step != Step::Stay) {
            currentBattery--;
        }

        // Check battery state
        if (currentBattery <= 0 && !atDockingStation()) {
            std::cout << "Simulation failed: battery exhausted.\n";
            return;
        }

        currentSteps++;
    }

    std::cout << "Simulation failed: maximum steps reached.\n";
}

bool MySimulator::atDockingStation() const {
    // Implement a method to check if the vacuum cleaner is at the docking station
    return false;
}
