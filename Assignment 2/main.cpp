#include "MySimulator.h"
#include "MyAlgorithm.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: myrobot <house_input_file>\n";
        return 1;
    }

    std::string houseFilePath = argv[1];
    MySimulator simulator;
    simulator.readHouseFile(houseFilePath);

    MyAlgorithm algo;
    simulator.setAlgorithm(algo);
    simulator.run();

    return 0;
}
