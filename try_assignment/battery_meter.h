#ifndef BATTERY_METER_H_
#define BATTERY_METER_H_

#include <cstddef>

/**
 * @class BatteryMeter
 * @brief An abstract class representing the battery meter for the vacuum cleaner.
 */
class BatteryMeter {
public:
	virtual ~BatteryMeter() {}

    /**
     * @brief Get the current battery state.
     * @return The current battery state.
     */
	virtual std::size_t getBatteryState() const = 0;
};

#endif  // BATTERY_METER_H_
