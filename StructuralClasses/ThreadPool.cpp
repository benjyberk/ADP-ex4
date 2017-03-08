//
// Created by atara on 1/26/17.
//

#include "ThreadPool.h"
#include <unistd.h>
using namespace std;

ThreadPool::ThreadPool(int pool_size)
{
    m_pool_size = pool_size;
    stop = false;
    if (pthread_mutex_init(&taskLock, NULL) != 0) {
        //"Mutex initialization failed"
    }

    // Initialization for all threads, sends them to the start_thread method
    for (int i = 0; i < m_pool_size; i++) {
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, start_thread, (void*) this);
        if (ret != 0)
        {
            /*error creating thread*/
        }
        m_threads.push_back(tid);
    }
}

ThreadPool::~ThreadPool()
{
    // Setting stop to true removes all threads from their endless 'wait' loops
    stop = true;
    for (int i = 0; i < m_pool_size; i++)
    {
        pthread_join(m_threads[i], NULL);
    }
    while (!m_tasks.empty()) {
        delete m_tasks.front();
        m_tasks.pop_front();
    }
    pthread_mutex_destroy(&taskLock);
}

void* ThreadPool::execute_thread()
{
    Task* task = NULL;
    // The overall running loop only terminates when given the signal (by the destructor)
    while(stop == false) {
        // While there are no tasks to do, the threads wait in an endless loop
        while (m_tasks.empty() && stop == false)
        {
            sleep(1);
        }
        // We Lock, to make sure only one thread gets one task at a time
        pthread_mutex_lock(&taskLock);
        if (!m_tasks.empty()) {
            // Assigns the first task in line to the thread
            task = m_tasks.front();
            m_tasks.pop_front();
            // Any other threads released can now get assigned the next task
            pthread_mutex_unlock(&taskLock);
            (*task)();

            // After the task is completed, it may be deleted
            delete task;
        }
        else {
            // If a thread was released from the endless loop simultaneously with the correct thread
            // It simply goes back to 'sleep'
            pthread_mutex_unlock(&taskLock);
        }
    }
    return NULL;
}

int ThreadPool::add_task(Task* task)
{
    m_tasks.push_back(task);
}

void* ThreadPool::start_thread(void *arg)
{
    ThreadPool* tp = (ThreadPool*) arg;
    tp->execute_thread();
    return NULL;
}