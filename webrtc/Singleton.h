#ifndef WEBRTC_CPP_DEMO_SINGLETON_H
#define WEBRTC_CPP_DEMO_SINGLETON_H

#include <memory>
#include <mutex>

namespace vic {
    template<typename T>
    class Singleton {
    public:
        virtual ~Singleton() {}
        static std::unique_ptr<T> &instance() {
            static std::unique_ptr<T> _instance = nullptr;
            static std::once_flag ocf;
            std::call_once(ocf, []() {
                _instance.reset(new T);
            });
            return _instance;
        }
    };
}

#endif //WEBRTC_CPP_DEMO_SINGLETON_H
