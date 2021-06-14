#ifndef SERVER_SRC_THREAD_H_
#define SERVER_SRC_THREAD_H_

#include <thread>
#include <utility>
#include <atomic>

class Thread {
    private:
        std::thread thread;
    protected:
        std::atomic<bool> is_running;
    public:
        Thread();
        void start();
        void join();
        virtual void run() = 0;
        virtual ~Thread();
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
        Thread(Thread&& other);
        Thread& operator=(Thread&& other);
        bool isDead() const;
};

#endif  // SERVER_SRC_THREAD_H_
