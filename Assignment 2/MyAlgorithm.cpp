#include "MyAlgorithm.h"
#include <vector>
#include <utility>
#include <stack>
#include <queue>

void MyAlgorithm::setMaxSteps(std::size_t maxSteps) {
    this->maxSteps = maxSteps;
}

void MyAlgorithm::setWallsSensor(const WallsSensor& wallsSensor) {
    this->wallsSensor = &wallsSensor;
}

void MyAlgorithm::setDirtSensor(const DirtSensor& dirtSensor) {
    this->dirtSensor = &dirtSensor;
}

void MyAlgorithm::setBatteryMeter(const BatteryMeter& batteryMeter) {
    this->batteryMeter = &batteryMeter;
}

Step MyAlgorithm::nextStep() {
    // Example implementation of a simple DFS-based exploration algorithm
    if (!steps.empty()) {
        Step next = steps.front();
        steps.pop();
        return next;
    }

    return Step::Finish;
}

// Example of simple DFS-based exploration to find all dirt and clean it
void MyAlgorithm::exploreHouse() {
    std::stack<std::pair<int, int>> stack;
    stack.push({0, 0});
    visited.insert({0, 0});

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        stack.pop();
        directions.push({x, y});

        if (dirtSensor->dirtLevel() > 0) {
            for (int i = 0; i < dirtSensor->dirtLevel(); ++i) {
                steps.push(Step::Stay);
            }
        }

        for (const auto& [dx, dy, step] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            if (visited.count({nx, ny}) == 0 && !wallsSensor->isWall(step)) {
                stack.push({nx, ny});
                visited.insert({nx, ny});
                steps.push(step);
            }
        }
    }

    // Add steps to return to docking station
    while (!directions.empty()) {
        auto [x, y] = directions.top();
        directions.pop();
        if (x < 0) {
            steps.push(Step::West);
        } else if (x > 0) {
            steps.push(Step::East);
        }
        if (y < 0) {
            steps.push(Step::North);
        } else if (y > 0) {
            steps.push(Step::South);
        }
    }
}
