//
// Created by atara on 1/26/17.
//

#ifndef ADP_EX4_TASK_H
#define ADP_EX4_TASK_H
class Task
{
public:
    //the constructor revceives a function and the args to the function as params
    Task(void *(*func_ptr)(void*), void* arg);
    ~Task();
    void operator()();
private:
    void* (*m_func_ptr)(void*);
    void* m_arg;
};
#endif //ADP_EX4_TASK_H
