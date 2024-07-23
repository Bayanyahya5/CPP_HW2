#include "MyDirt_sensor.h"

MyDirt_sensor::MyDirt_sensor(std::vector<std::vector<int>> &dirtLevels, int row, int col)
    : dirtLevels_(dirtLevels), row_(row), col_(col) {}

int MyDirt_sensor::dirtLevel() const
{
    return dirtLevels_[row_][col_];
}

void MyDirt_sensor::setPosition(int row, int col)
{
    row_ = row;
    col_ = col;
}

int MyDirt_sensor::houseDirtLevel() const
{
    int dirtSum = 0;
    for (const std::vector<int> &row : dirtLevels_)
    {
        for (const int dirtLevel : row)
        {
            dirtSum += dirtLevel;
        }
    }
    return dirtSum;
}

void MyDirt_sensor::cleen()
{
    dirtLevels_[row_][col_]--;
}