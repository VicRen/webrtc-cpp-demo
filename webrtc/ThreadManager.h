#ifndef WEBRTC_CPP_DEMO_THREADMANAGER_H
#define WEBRTC_CPP_DEMO_THREADMANAGER_H

#include <unordered_map>
#include <atomic>
#include <mutex>

#include "Singleton.h"
#include "rtc_base/thread.h"

namespace vic::rtc {
    enum class ThreadName : int {
        MAIN = 0,
        WORKER = 1,
        SERVICE = 2,
    }; // enum ThreadName

    class ThreadManager : public Singleton<ThreadManager> {
    public:

        ThreadManager(const ThreadManager &) = delete;

        ThreadManager(ThreadManager &&) = delete;

        ~ThreadManager() override;

        void init();

        static void destroy();

        ::rtc::Thread *thread(ThreadName name);

    private:
        ThreadManager();

        ThreadManager &operator=(const ThreadManager &) = default;

    private:
        void stopAll();

    private:
        std::unordered_map<ThreadName, std::shared_ptr<::rtc::Thread>> _threadsMap;

        std::mutex _mutex;

        ::rtc::Thread *_mainThread = nullptr;

        std::atomic_bool _destroy;

        friend class ::vic::Singleton<ThreadManager>;
    };
} // namespace vic::rtc


#endif //WEBRTC_CPP_DEMO_THREADMANAGER_H
