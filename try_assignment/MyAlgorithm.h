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

/**
 * @class MyAlgorithm
 * @brief Implements a deterministic algorithm for the vacuum cleaner using DFS.
 */
class MyAlgorithm : public AbstractAlgorithm
{
public:
    void setMaxSteps(std::size_t maxSteps) override;
    void setWallsSensor(const WallsSensor &) override;
    void setDirtSensor(const DirtSensor &) override;
    void setBatteryMeter(const BatteryMeter &) override;
    Step nextStep() override;

    /**
     * @brief Set the docking station coordinates.
     * @param row The row of the docking station.
     * @param col The column of the docking station.
     */
    void setDockingStation(int row, int col); // Set the docking station coordinates
    
    /**
     * @brief Set the current position of the vacuum cleaner.
     * @param row The current row.
     * @param col The current column.
     */
    void setPosition(int row, int col);
    
    /**
     * @brief Clear the set of visited positions.
     */
    void clearVisited();

private:
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

/**
 * @brief Determines the direction to move based on the current and new coordinates.
 * 
 * This function compares the current position with the new position and returns 
 * the corresponding direction to move.
 * 
 * @param newRow The row coordinate of the new position.
 * @param newCol The column coordinate of the new position.
 * @return Direction The direction to move (North, South, East, or West).
 */
    Direction moveToDirection(int newRow, int newCol);

/**
 * @brief Determines the step to take based on the current and new coordinates.
 * 
 * This function compares the current position with the new position and returns 
 * the corresponding step to take.
 * 
 * @param newRow The row coordinate of the new position.
 * @param newCol The column coordinate of the new position.
 * @return Step The step to take (North, South, East, West, or Stay).
 */
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