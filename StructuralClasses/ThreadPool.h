//
// Created by atara on 1/26/17.
//

#ifndef ADP_EX4_THREADPOOL_H
#define ADP_EX4_THREADPOOL_H
#include <deque>
#include "Task.h"
#include "pthread.h"
#include "iostream"
#include <vector>

class ThreadPool
{
public:
    ThreadPool(int pool_size);
    ~ThreadPool();
    void* execute_thread();
    int add_task(Task* task);
private:
    bool stop;
    int m_pool_size;
    std::vector<pthread_t> m_threads;
    std::deque<Task*> m_tasks;
    static void* start_thread(void* arg);
    pthread_mutex_t taskLock;
};
#endif //ADP_EX4_THREADPOOL_H