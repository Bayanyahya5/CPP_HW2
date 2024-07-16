#ifndef MYVACUUM_H
#define MYVACUUM_H

#include <string>
#include <vector>

class MyVacuum

{
private:
    /*
x_DockingStation is the x-axis location of the station
y_DockingStation is the y-axis location of the station
 */
    int x_DockingStation, y_DockingStation;

    /*
x is the x-axis location of the vacuum cleaner
y is the y-axis location of the vacuum cleaner
 */
    int x, y;

    /*
   the battery of the vacuum cleaner
    */
    std::size_t battery;

    /*
    the max battery of the vacuum cleaner
     */
    std::size_t max_battery;

    /*
the max steps of the vacuum cleaner
 */
    std::size_t max_steps;

    /*
    the total steps of the vacuum cleaner
     */
    std::size_t total_steps;

    /*
vector that contains pairs of the locations to get back to the docking station
 */
    std::vector<std::pair<int, int>> back_steps;

    /*
vector that contains pairs of the locations of all the steps
 */
    std::vector<std::pair<int, int>> all_steps;

public:
    /*
     *constructor of MyVacuum
      class
     *@param start_x: x-axis of the start locations
     *@param start_y: y-axis of the start locations
     *@param max_battery: the max_battery of the vacuum cleaner
     *@param max_steps: the max_steps of the vacuum cleaner
     */
    MyVacuum
    (int start_x, int start_y, double max_battery, int max_steps);

    /*
     *destructor of MyVacuum
      class
     */
     ~MyVacuum
     ();


    /*
     *this function called when the vacuum moves.
     *@param direction: direction to move
     *decreasing the battery level by 1
     *increasing the total steps by 1
     *updating the back_steps and the all_steps vec
     *updating the current location (x,y)
     */
    void move(char direction);

    /*
     *charge the vacuum
     *increasing the total_steps by 1
     */
    void charge();

    /*
     *clean the location
     *increasing the total_steps by 1
     *updating the all_steps vec
     */
    void clean();

    /*
     *this function called to check if the vacuum out of battery
     *return: True if the vacuum out of the battery, if not return False
     */
    bool isOutOfBattery() const;

    /*
     *this function called to get the Docking station
     *return: pair of the docking station location
     */
    std::pair<int, int> getPosition() const;

    /*
     *this function called to get the battery level of the vacuum cleaner
     *return: the battary level of the vacuum cleaner
     */
    double getBatteryLevel() const;

    /*
     *this function called to get the total steps
     *return: the total steps
     */
    int getTotalSteps() const;

    /*
     *this function called to check if the vacuum out of steps
     *return: True if the vacuum out of the steps, if not return False
     */
    bool IsOutOfSteps() const;

    /*
     *this function called to get the total steps of the vacuum cleaner
     *return: vector that contains pairs of the locations to get back to the docking station
     */
    std::vector<std::pair<int, int>> getBack_steps() const;

    /*
     *this function called to get the total steps of the vacuum cleaner
     *return: vector that contains pairs of the locations of all the steps
     */
    std::vector<std::pair<int, int>> getAll_steps() const;

    /*
     *this function called to set the vacuum's docking station
     */
    void setPostionToDockingStation();

    /*
     *this function called to get the max steps that the vacuum cleaner can do
     *return: the max steps of the vacuum cleaner
     */
    int getMaxSteps() const;

    /*
     *this function called to get the max battery that the vacuum cleaner
     *return: the max battery of the vacuum cleaner
     */
    double getMaxBattery() const;

    /*
     *this function called to check if the vacuum is in the docking station
     *return: True if the vacuum is in the docking station, if not return False
     */
    bool isInDockingStation() const;

    /*
     *this function called to get the number of steps to the docking station
     *return: the number of the steps to the docking station
     */

    int getBack_stepsSize() const; 

    /*
     *this function called to get the number of all of the steps
     *return: the number of all of the steps
     */
    int getAll_stepsSize() const;
};

#endif
