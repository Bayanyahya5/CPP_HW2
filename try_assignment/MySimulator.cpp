#include "MySimulator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

void MySimulator::readHouseFile(const std::string& houseFilePath) {
    std::ifstream file(houseFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open house file" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // House name
    std::getline(file, line); // MaxSteps
    maxSteps_ = std::stoi(line.substr(line.find('=') + 1));
    std::getline(file, line); // MaxBattery
    maxBattery_ = std::stoi(line.substr(line.find('=') + 1));
    std::getline(file, line); // Rows
    int rows = std::stoi(line.substr(line.find('=') + 1));
    std::getline(file, line); // Cols
    int cols = std::stoi(line.substr(line.find('=') + 1));

    house_.resize(rows, std::vector<char>(cols, ' '));
    dirtLevels_.resize(rows, std::vector<int>(cols, 0));

    int row = 0;
    while (std::getline(file, line)) {
        for (int col = 0; col < cols && col < line.size(); ++col) {
            house_[row][col] = line[col];
            if (line[col] == 'D') {
                dockingRow_ = row;
                dockingCol_ = col;
            } else if (isdigit(line[col])) {
                dirtLevels_[row][col] = line[col] - '0';
            }
        }
        ++row;
    }

    file.close();
    currentRow_ = dockingRow_;
    currentCol_ = dockingCol_;

    wallsSensor_ = std::make_unique<MyWall_sensor>(house_, currentRow_, currentCol_);
    dirtSensor_ = std::make_unique<MyDirt_sensor>(dirtLevels_, currentRow_, currentCol_);
    batteryMeter_ = std::make_unique<MyBattery_meter>(maxBattery_);
}

void MySimulator::setAlgorithm(AbstractAlgorithm& algo) {
    algo.setMaxSteps(maxSteps_);
    algo.setWallsSensor(*wallsSensor_);
    algo.setDirtSensor(*dirtSensor_);
    algo.setBatteryMeter(*batteryMeter_);
}

void MySimulator::run() {
    MyAlgorithm algo;
    setAlgorithm(algo);

    currentStep_ = 0;
    while (currentStep_ < maxSteps_) {
        Step step = algo.nextStep();
        steps_.push_back("NESWsF"[static_cast<int>(step)]);
        currentStep_++;

        if (step == Step::Finish) {
            break;
        } else if (step == Step::Stay) {
            int dirt = dirtSensor_->dirtLevel();
            if (dirt > 0) {
                dirtLevels_[currentRow_][currentCol_]--;
            }
            batteryMeter_->decreaseBattery();
        } else {
            switch (step) {
                case Step::North: currentRow_--; break;
                case Step::East:  currentCol_++; break;
                case Step::South: currentRow_++; break;
                case Step::West:  currentCol_--; break;
                default: break;
            }
            batteryMeter_->decreaseBattery();
            updateSensors();
        }

        if (batteryMeter_->getBatteryState() == 0) {
            steps_.push_back('F');
            break;
        }
    }

    // Write output file
    std::ofstream outFile("output.txt");
    outFile << "NumSteps = " << currentStep_ << "\n";
    outFile << "DirtLeft = " << dirtSensor_->dirtLevel() << "\n"; ////////////////////////////////////////////// change
    outFile << "Status = " << ((steps_.back() == 'F') ? "FINISHED" : "WORKING") << "\n"; /////////////////////////////// check
    outFile << "Steps: ";
    for (char step : steps_) {
        outFile << step;
    }
    outFile << "\n";
    outFile.close();
}

void MySimulator::updateSensors() {
    wallsSensor_->setPosition(currentRow_, currentCol_);
    dirtSensor_->setPosition(currentRow_, currentCol_);
}
