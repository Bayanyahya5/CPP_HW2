#include "MyDirtSensor.h"

int MyDirtSensor::dirtLevel() const {
    int dirtLevel = 0;/////////////////////////////////////////////////
    for (size_t i = 0; i < house.size(); i++)
    {
        for (size_t j = 0; j < house[i].size(); i++)
        {
            if (house[i][j] != 'W' && house[i][j] != ' ' && house[i][j] != 'D')
            {
                dirtLevel += house[i][j] - '0';
            }
        }
    }
    return dirtLevel;/////////////////////////////////////////////
    // return 0;
}
