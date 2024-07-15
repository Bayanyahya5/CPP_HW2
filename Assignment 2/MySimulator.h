#ifndef MY_SIMULATOR_H
#define MY_SIMULATOR_H

#include <string>
#include <vector>
#include "MyAlgorithm.h"

class MySimulator {
    std::string houseName;
    std::size_t maxSteps;
    std::size_t maxBattery;
    std::size_t rows;
    std::size_t cols;
    std::vector<char> house;
    MyAlgorithm* algo;

public:
    void readHouseFile(const std::string& houseFilePath);
    void setAlgorithm(MyAlgorithm& algorithm);
    void run();
};

#endif // MY_SIMULATOR_H
