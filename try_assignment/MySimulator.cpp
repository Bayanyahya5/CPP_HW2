#include "MySimulator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

void MySimulator::readHouseFile(const std::string &houseFilePath)
{
    std::ifstream file(houseFilePath);
    if (!file.is_open())
    {
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
    while (std::getline(file, line))
    {
        for (int col = 0; col < cols && col < line.size(); ++col)
        {
            house_[row][col] = line[col];
            if (line[col] == 'D')
            {
                dockingRow_ = row;
                dockingCol_ = col;
            }
            else if (isdigit(line[col]))
            {
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

void MySimulator::setAlgorithm(MyAlgorithm &algo)
{
    algo_ = algo;
    algo.setMaxSteps(maxSteps_);
    algo.setWallsSensor(*wallsSensor_);
    algo.setDirtSensor(*dirtSensor_);
    algo.setBatteryMeter(*batteryMeter_);
}

void MySimulator::run()
{
    currentStep_ = 0;
    while (currentStep_ < maxSteps_ && batteryMeter_->getBatteryState() != 0)
    {
        if (batteryMeter_->getBatteryState() <= back_steps_.size() + 1 && maxSteps_ > (currentStep_ + back_steps_.size())) /// can return to the docking station cause return will not pass the legal number of maxSteps
        {
            if (batteryMeter_->getBatteryState() == back_steps_.size() + 1 && dirtSensor_->dirtLevel() > 0)
            {
                steps_.push_back('s');
                dirtLevels_[currentRow_][currentCol_]--;
                batteryMeter_->decreaseBattery();
                currentStep_++;
            }
            need_charge();
            continue;
        }

        Step step = algo_.nextStep();
        steps_.push_back("NESWsF"[static_cast<int>(step)]);

        if (step == Step::Finish)
        {
            break;
        }
        else if (step == Step::Stay)
        {
            dirtLevels_[currentRow_][currentCol_]--; /////////////////////////////// remove dirtLevels_ and stay with one victor
        }
        else
        {
            switch (step)
            {
            case Step::North:
                currentRow_--;
                back_steps_.push_back('S');
                break;
            case Step::East:
                currentCol_++;
                back_steps_.push_back('W');
                break;
            case Step::South:
                currentRow_++;
                back_steps_.push_back('N');
                break;
            case Step::West:
                currentCol_--;
                back_steps_.push_back('E');
                break;
            default:
                break;
            }
            updateSensors();
        }
        batteryMeter_->decreaseBattery();
        currentStep_++;
    }

    // Write output file
    std::ofstream outFile("output.txt");
    outFile << "NumSteps = " << currentStep_ << "\n";
    outFile << "DirtLeft = " << dirtSensor_->houseDirtLevel() << "\n";
    if(batteryMeter_->getBatteryState() == 0 && (currentRow_ != dockingRow_ || currentCol_ != dockingCol_)){
        outFile << "Status = " << "DEAD" << "\n";
    }
    else{
        outFile << "Status = " << ((steps_.back() == 'F') ? "FINISHED" : "WORKING") << "\n";
    }
    outFile << "Steps: ";
    for (char step : steps_)
    {
        outFile << step;
    }
    outFile << "\n";
    outFile.close();
}

void MySimulator::updateSensors()
{
    wallsSensor_->setPosition(currentRow_, currentCol_);
    dirtSensor_->setPosition(currentRow_, currentCol_);
}

void MySimulator::need_charge()
{
    for(int i = back_steps_.size() - 1; i >= 0; i--)
    {
        steps_.push_back(back_steps_[i]);
    }
    currentRow_ =  dockingRow_;
    currentCol_ = dockingCol_;
    currentStep_ += back_steps_.size();
    back_steps_.clear();

    while(currentStep_ < maxSteps_ && batteryMeter_->getBatteryState() < maxBattery_)
    {
        batteryMeter_->chargeBattery();
        currentStep_++;
        steps_.push_back('s');
    }
    updateSensors();
}
