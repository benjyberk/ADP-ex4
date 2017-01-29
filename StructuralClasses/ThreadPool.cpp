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

    for (int i = 0; i < m_pool_size; i++) {
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, start_thread, (void*) this);
        if (ret != 0)
        {
            /*error creating thread*/
        }
        m_threads.push_back(tid);
    }
    cout << m_pool_size << " threads created by the thread pool" << endl;
}

ThreadPool::~ThreadPool()
{
    stop = true;
    for (int i = 0; i < m_pool_size; i++)
    {

        pthread_join(m_threads[i], NULL);
    }
    cout << "Destroying task lock" << endl;
    pthread_mutex_destroy(&taskLock);
    cout << m_pool_size << " threads exited from the thread pool" << endl;
}

void* ThreadPool::execute_thread()
{
    Task* task = NULL;
    while(stop == false) {
        while (m_tasks.empty() && stop == false)
        {
            sleep(1);
        }
        pthread_mutex_lock(&taskLock);
        cout << "Locked Task" << endl;
        if (!m_tasks.empty()) {
            cout << "Doing Task" << endl;
            task = m_tasks.front();
            m_tasks.pop_front();
            cout << "Unlocking Task" << endl;
            pthread_mutex_unlock(&taskLock);
            (*task)();
        }
        else {
            cout << "Returning to sleep" << endl;
            cout << "Unlocking Task" << endl;
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