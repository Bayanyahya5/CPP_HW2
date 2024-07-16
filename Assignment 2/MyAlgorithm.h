#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include "AbstractAlgorithm.h"
#include "WallsSensor.h"
#include "DirtSensor.h"
#include "BatteryMeter.h"
#include <set>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

class MyAlgorithm : public AbstractAlgorithm {
public:
    void setMaxSteps(std::size_t maxSteps) override;
    void setWallsSensor(const WallsSensor& wallsSensor) override;
    void setDirtSensor(const DirtSensor& dirtSensor) override;
    void setBatteryMeter(const BatteryMeter& batteryMeter) override;
    Step nextStep() override;

private:
    std::size_t maxSteps;
    const WallsSensor* wallsSensor;
    const DirtSensor* dirtSensor;
    const BatteryMeter* batteryMeter;
    std::queue<Step> steps;

    std::set<std::pair<int, int>> visited;
    std::stack<std::pair<int, int>> directions;
    void exploreHouse();
};

#endif // MYALGORITHM_H
