#include "MyVacuum.h"
#include <iostream>

/*
 *constructor of MyVacuum class
 *@param start_x: x-axis of the start locations
 *@param start_y: y-axis of the start locations
 *@param max_battery: the max_battery of the vacuum cleaner
 *@param max_steps: the max_steps of the vacuum cleaner
 */
MyVacuum::MyVacuum(int start_x, int start_y, double max_battery, int max_steps)
    : x(start_x), y(start_y), battery(max_battery), max_battery(max_battery), max_steps(max_steps), total_steps(0), x_DockingStation(start_x), y_DockingStation(start_y) {}


MyVacuum::~MyVacuum() {
}


/*
 *this function called when the vacuum moves.
 *@param direction: direction to move
 *decreasing the battery level by 1
 *increasing the total steps by 1
 *updating the back_steps and the all_steps vec
 *updating the current location (x,y)
 */
void MyVacuum::move(char direction)
{
    back_steps.push_back(std::make_pair(x, y));
    switch (direction)
    {
    case 'N':
        x--;
        break;
    case 'E':
        y++;
        break;
    case 'S':
        x++;
        break;
    case 'W':
        y--;
        break;
    }
    battery--;
    total_steps++;
    all_steps.push_back(std::make_pair(x, y));
}

/*
 *charge the vacuum
 *increasing the total_steps by 1
 */
void MyVacuum::charge()
{
    if (battery + (max_battery / 20) > max_battery)
    {
        battery = max_battery;
    }
    else
    {
        battery += max_battery / 20;
    }

    total_steps++;
    all_steps.push_back(std::make_pair(x_DockingStation, y_DockingStation));
}

/*
 *clean the location
 *increasing the total_steps by 1
 *updating the all_steps vec
 */
void MyVacuum::clean()
{
    battery--;
    total_steps++;
    all_steps.push_back(std::make_pair(x, y));
}

/*
 *this function called to check if the vacuum out of battery
 *return: True if the vacuum out of the battery, if not return False
 */
bool MyVacuum::isOutOfBattery() const
{
    return battery == 0;
}

/*
 *this function called to get the Docking station
 *return: pair of the docking station location
 */
std::pair<int, int> MyVacuum::getPosition() const
{
    return {x, y};
}

/*
 *this function called to get the battery level of the vacuum cleaner
 *return: the battary level of the vacuum cleaner
 */
double MyVacuum::getBatteryLevel() const
{
    return battery;
}

/*
 *this function called to get the total steps
 *return: the total steps
 */
int MyVacuum::getTotalSteps() const
{
    return total_steps;
}

/*
 *this function called to check if the vacuum out of steps
 *return: True if the vacuum out of the steps, if not return False
 */
bool MyVacuum::IsOutOfSteps() const
{
    return max_steps == total_steps;
}

/*
 *this function called to get the total steps of the vacuum cleaner
 *return: vector that contains pairs of the locations to get back to the docking station
 */
std::vector<std::pair<int, int>> MyVacuum::getBack_steps() const
{
    return back_steps;
}

/*
 *this function called to get the total steps of the vacuum cleaner
 *return: vector that contains pairs of the locations of all the steps
 */
std::vector<std::pair<int, int>> MyVacuum::getAll_steps() const
{
    return all_steps;
}

/*
 *this function called to set the vacuum's docking station
 *updating the current location of the vacuum cleaner (x,y)
 *increasing total steps
 *clearing back_steps vec
 */
void MyVacuum::setPostionToDockingStation()
{
    for (int i = getBack_stepsSize() - 1; i >= 0; i--)
    {
        all_steps.push_back(back_steps[i]);
        battery--;
    }
    x = x_DockingStation;
    y = y_DockingStation;
    total_steps += back_steps.size();
    back_steps.clear();
}

/*
 *this function called to get the max steps that the vacuum cleaner can do
 *return: the max steps of the vacuum cleaner
 */
int MyVacuum::getMaxSteps() const
{
    return max_steps;
}

/*
 *this function called to get the max battery that the vacuum cleaner
 *return: the max battery of the vacuum cleaner
 */
double MyVacuum::getMaxBattery() const
{
    return max_battery;
}

/*
 *this function called to check if the vacuum is in the docking station
 *return: True if the vacuum is in the docking station, if not return False
 */
bool MyVacuum::isInDockingStation() const
{
    if (x != x_DockingStation || y != y_DockingStation)
    {
        return false;
    }
    return true;
}

/*
 *this function called to get the number of steps to the docking station
 *return: the number of the steps to the docking station
 */
int MyVacuum::getBack_stepsSize() const
{
    int cnt = 0;
    for (std::pair<int, int> pair : back_steps)
    {
        cnt++;
    }
    return cnt;
}

/*
 *this function called to get the number of all of the steps
 *return: the number of all of the steps
 */
int MyVacuum::getAll_stepsSize() const
{
    int cnt = 0;
    for (std::pair<int, int> pair : all_steps)
    {
        cnt++;
    }
    return cnt;
}