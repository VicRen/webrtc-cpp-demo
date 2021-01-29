#include "StatsReporter.h"
#include <iostream>

int64_t StatsReporter::TimeUntilNextProcess() {
    return 5000;
}

void StatsReporter::Process() {
    std::cout << "-------->StatsReporter Processing" << std::endl;
}
