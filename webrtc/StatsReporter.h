#ifndef WEBRTC_CPP_DEMO_STATSREPORTER_H
#define WEBRTC_CPP_DEMO_STATSREPORTER_H

#include "modules/include/module.h"

class StatsReporter : public webrtc::Module {
private:
    int64_t TimeUntilNextProcess() override;

    void Process() override;
};


#endif //WEBRTC_CPP_DEMO_STATSREPORTER_H
