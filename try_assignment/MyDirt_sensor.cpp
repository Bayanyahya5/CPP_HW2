#include "MyDirt_sensor.h"

MyDirt_sensor::MyDirt_sensor(const std::vector<std::vector<int>>& dirtLevels, int row, int col)
    : dirtLevels_(dirtLevels), row_(row), col_(col) {}

int MyDirt_sensor::dirtLevel() const {
    return dirtLevels_[row_][col_];
}

void MyDirt_sensor::setPosition(int row, int col) {
    row_ = row;
    col_ = col;
}
