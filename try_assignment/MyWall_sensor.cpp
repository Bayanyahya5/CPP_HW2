#include "MyWall_sensor.h"

MyWall_sensor::MyWall_sensor(const std::vector<std::vector<char>>& house, int row, int col)
    : house_(house), row_(row), col_(col) {}

bool MyWall_sensor::isWall(Direction d) const {
    int newRow = row_;
    int newCol = col_;
    switch (d) {
        case Direction::North: newRow--; break;
        case Direction::East:  newCol++; break;
        case Direction::South: newRow++; break;
        case Direction::West:  newCol--; break;
    }
    return house_[newRow][newCol] == 'W';
}

void MyWall_sensor::setPosition(int row, int col) {
    row_ = row;
    col_ = col;
}
