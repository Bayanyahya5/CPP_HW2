#ifndef MYSIMULATOR_H
#define MYSIMULATOR_H

#include <string>
#include <vector>
#include <memory>
#include "MyAlgorithm.h"

/**
 * @class MySimulator
 * @brief Manages the simulation of the vacuum cleaner.
 */
class MySimulator
{
public:

    /**
     * @brief Read the house configuration from a file.
     * @param houseFilePath The path to the house file.
     */
    void readHouseFile(const std::string &houseFilePath);

    /**
     * @brief Set the algorithm to be used in the simulation.
     * @param algo The algorithm.
     */
    void setAlgorithm(MyAlgorithm &algo);

    /**
     * @brief Run the simulation.
     */
    void run();

private:
    MyAlgorithm algo_;
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
    std::size_t currentSteps_;
    std::vector<char> steps_;
    std::vector<char> back_steps_;
    std::string houseFileName;

    /**
     * @brief Update the sensors with the current position.
     */
    void updateSensors();

    /**
     * @brief Handle the need to charge the battery.
     */
    void need_charge();

    /**
     * @brief Check if the current step is a back step.
     * @param new_step The new step.
     * @param old_step The old step.
     * @return True if the current step is a back step, false otherwise.
     */
    bool step_back(char new_step, char old_step);
};

#endif // MYSIMULATOR_H