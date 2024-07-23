#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include "abstract_algorithm.h"
#include "MyWall_sensor.h"
#include "MyDirt_sensor.h"
#include "MyBattery_meter.h"
#include <memory>
#include <stack>
#include <set>
#include <utility> // For std::pair

#include <iostream> ///////////////////////////////

class MyAlgorithm : public AbstractAlgorithm
{
public:
    void setMaxSteps(std::size_t maxSteps) override;
    void setWallsSensor(const WallsSensor &) override;
    void setDirtSensor(const DirtSensor &) override;
    void setBatteryMeter(const BatteryMeter &) override;
    Step nextStep() override;

    void setDockingStation(int row, int col); // Set the docking station coordinates
    void setPosition(int row, int col);
    void clearVisited();

private:
    // const WallsSensor* wallsSensor_;
    // const DirtSensor* dirtSensor_;
    // const BatteryMeter* batteryMeter_;
    std::shared_ptr<const WallsSensor> wallsSensor_;
    std::shared_ptr<const DirtSensor> dirtSensor_;
    std::shared_ptr<const BatteryMeter> batteryMeter_;
    std::size_t maxSteps_;
    std::size_t currentSteps_;

    std::stack<std::pair<int, int>> dfsStack_; // Stack for DFS
    std::set<std::pair<int, int>> visited_;    // Set for visited positions
    std::set<std::pair<int, int>> cant_move_;
    int currentRow_;
    int currentCol_;
    int dockingRow_;
    int dockingCol_;

    Direction moveToDirection(int newRow, int newCol);
    Step moveToStep(int newRow, int newCol);

    std::vector<std::vector<int>> groups = {
        {2, 3, 1, 4},
        {1, 4, 3, 2},
        {3, 2, 4, 1},
        {4, 2, 1, 3},
        {1, 3, 2, 4},
        {3, 1, 4, 2},
        {2, 1, 4, 3},
        {4, 3, 2, 1},
        {1, 2, 3, 4},
        {2, 4, 3, 1},
        {3, 4, 1, 2},
        {4, 1, 3, 2},
        {1, 2, 4, 3},
        {2, 3, 4, 1},
        {3, 1, 2, 4},
        {4, 1, 2, 3},
        {1, 3, 4, 2},
        {2, 4, 1, 3},
        {3, 2, 1, 4},
        {4, 2, 3, 1},
        {1, 4, 2, 3},
        {2, 1, 3, 4},
        {3, 4, 2, 1},
        {4, 3, 1, 2}};
    int index = 0;
};

#endif // MYALGORITHM_H