#include "MyAlgorithm.h"

void MyAlgorithm::setMaxSteps(std::size_t maxSteps)
{
    maxSteps_ = maxSteps;
}

void MyAlgorithm::setWallsSensor(const WallsSensor &sensor)
{
    wallsSensor_ = std::shared_ptr<const WallsSensor>(&sensor, [](const WallsSensor *) {});
}

void MyAlgorithm::setDirtSensor(const DirtSensor &sensor)
{
    dirtSensor_ = std::shared_ptr<const DirtSensor>(&sensor, [](const DirtSensor *) {});
}

void MyAlgorithm::setBatteryMeter(const BatteryMeter &meter)
{
    batteryMeter_ = std::shared_ptr<const BatteryMeter>(&meter, [](const BatteryMeter *) {});
}

void MyAlgorithm::setDockingStation(int row, int col)
{
    dockingRow_ = row;
    dockingCol_ = col;
    currentRow_ = row;
    currentCol_ = col;
    dfsStack_.push({currentRow_, currentCol_});
    visited_.insert({currentRow_, currentCol_});
}

Direction MyAlgorithm::moveToDirection(int newRow, int newCol)
{
    if (newRow < currentRow_)
        return Direction::North;
    if (newRow > currentRow_)
        return Direction::South;
    if (newCol < currentCol_)
        return Direction::West;
    return Direction::East;
}

Step MyAlgorithm::moveToStep(int newRow, int newCol)
{
    if (newRow < currentRow_)
        return Step::North;
    if (newRow > currentRow_)
        return Step::South;
    if (newCol < currentCol_)
        return Step::West;
    return Step::East;
}

void MyAlgorithm::setPosition(int row, int col)
{
    currentRow_ = row;
    currentCol_ = col;
}

void MyAlgorithm::clearVisited()
{
    visited_.clear();
    visited_.insert({currentRow_, currentCol_});
    std::stack<std::pair<int, int>> emptyStack;
    std::swap(dfsStack_, emptyStack);
    dfsStack_.push({currentRow_, currentCol_});
}

Step MyAlgorithm::nextStep()
{
    if (dirtSensor_->dirtLevel() > 0)
    {
        return Step::Stay;
    }
    std::pair<int, int> currentPos = dfsStack_.top();
    int row = currentRow_;
    int col = currentCol_;

    // Check and move to adjacent unvisited and non-wall cells
    std::pair<int, int> orig_neighbors[] = {
        {row - 1, col}, // North
        {row + 1, col}, // South
        {row, col - 1}, // West
        {row, col + 1}  // East
    };

    std::pair<int, int> neighbors[4];

    // Rearrange neighbors based on the group order
    for (int i = 0; i < 4; ++i)
    {
        neighbors[i] = orig_neighbors[groups[index][i] - 1];
    }
    index++;
    index = index % 24;

    for (const std::pair<int, int> &neighbor : neighbors)
    {
        int newRow = neighbor.first;
        int newCol = neighbor.second;

        if (!wallsSensor_->isWall(moveToDirection(newRow, newCol)) && cant_move_.find(neighbor) == cant_move_.end() && visited_.find(neighbor) == visited_.end())
        {
            visited_.insert(currentPos);
            dfsStack_.push(neighbor);
            return moveToStep(newRow, newCol);
        }
    }

    if (currentRow_ == dockingRow_ && currentCol_ == dockingCol_)
    {
        return Step::Finish;
    }

    // If no unvisited neighbors, backtrack
    cant_move_.insert(currentPos);
    dfsStack_.pop();
    if (!dfsStack_.empty())
    {
        std::pair<int, int> backtrackPos = dfsStack_.top();
        return moveToStep(backtrackPos.first, backtrackPos.second);
    }

    return Step::Finish;
}
