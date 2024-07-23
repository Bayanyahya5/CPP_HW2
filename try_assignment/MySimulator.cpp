#include "MySimulator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

void MySimulator::readHouseFile(const std::string &houseFilePath)
{
    houseFileName = houseFilePath;
    try{
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
        row++;
        if (row == rows)
            break;
    }

    file.close();
    currentRow_ = dockingRow_;
    currentCol_ = dockingCol_;

    wallsSensor_ = std::make_unique<MyWall_sensor>(house_, currentRow_, currentCol_);
    dirtSensor_ = std::make_unique<MyDirt_sensor>(dirtLevels_, currentRow_, currentCol_);
    batteryMeter_ = std::make_unique<MyBattery_meter>(maxBattery_);
    
    }
        catch(const std::exception &e){
        std::cout << "--> Standard exception: " << e.what() << std::endl;
    }
}

void MySimulator::setAlgorithm(MyAlgorithm &algo)
{
    algo_ = algo;
    algo_.setMaxSteps(maxSteps_);
    algo_.setWallsSensor(*wallsSensor_);
    algo_.setDirtSensor(*dirtSensor_);
    algo_.setBatteryMeter(*batteryMeter_);
    algo_.setDockingStation(dockingRow_, dockingCol_);
}

void MySimulator::updateSensors()
{
    wallsSensor_->setPosition(currentRow_, currentCol_);
    dirtSensor_->setPosition(currentRow_, currentCol_);
    algo_.setPosition(currentRow_, currentCol_);
}

void MySimulator::need_charge()
{
    for (int i = back_steps_.size() - 1; i >= 0; i--)
    {
        steps_.push_back(back_steps_[i]);
    }
    currentRow_ = dockingRow_;
    currentCol_ = dockingCol_;
    currentSteps_ += back_steps_.size();
    back_steps_.clear();

    int cnt = 0;
    while (currentSteps_ < maxSteps_ && batteryMeter_->getBatteryState() < maxBattery_)
    {
        batteryMeter_->chargeBattery();
        currentSteps_++;
        steps_.push_back('s');
        cnt++;
    }

    if(currentSteps_ >= maxSteps_ - 1){
        currentSteps_ -= cnt;
        for (int i = 0; i < cnt; i++)
        {
            steps_.pop_back();
        }
        steps_.push_back('F');
    }
    updateSensors();
    algo_.clearVisited();
}

bool MySimulator::step_back(char new_step, char old_step)
{
    if (new_step == 'N' && old_step == 'S')
        return true;
    if (new_step == 'S' && old_step == 'N')
        return true;
    if (new_step == 'E' && old_step == 'W')
        return true;
    if (new_step == 'W' && old_step == 'E')
        return true;
    return false;
}

void MySimulator::run()
{
    currentSteps_ = 0;
    while (currentSteps_ < maxSteps_ && batteryMeter_->getBatteryState() != 0)
    {
        if(steps_.size() > 0 && steps_.back() == 'F'){
            break;
        }
        if (currentRow_ == dockingRow_ && currentCol_ == dockingCol_ && (maxSteps_ - currentSteps_) == 1)
        {
            steps_.push_back('F');
            break;
        }

        if (batteryMeter_->getBatteryState() <= back_steps_.size() + 1 && maxSteps_ > (currentSteps_ + back_steps_.size())) /// can return to the docking station cause return will not pass the legal number of maxSteps
        {
            if (batteryMeter_->getBatteryState() == back_steps_.size() + 1 && dirtSensor_->dirtLevel() > 0)
            {
                steps_.push_back('s');
                dirtSensor_->cleen();
                batteryMeter_->decreaseBattery();
                currentSteps_++;
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
            dirtSensor_->cleen();        }
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
        currentSteps_++;
        if (back_steps_.size() >= 2)
        {
            if (step_back(back_steps_.back(), back_steps_[back_steps_.size() - 2]))
            {
                back_steps_.pop_back();
                back_steps_.pop_back();
            }
        }
    }

    // Write output file
    std::ofstream outFile("output_" + houseFileName);
    outFile << "NumSteps = " << currentSteps_ << "\n";
    outFile << "DirtLeft = " << dirtSensor_->houseDirtLevel() << "\n";
    if (batteryMeter_->getBatteryState() == 0 && (currentRow_ != dockingRow_ || currentCol_ != dockingCol_))
    {
        outFile << "Status = " << "DEAD" << "\n";
    }
    else
    {
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
