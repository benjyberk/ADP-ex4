//
// Created by atara on 1/26/17.
//

#include "Task.h"

Task::Task(void *(*fn_ptr)(void*), void* arg)
{
    m_func_ptr = fn_ptr;
    m_arg = arg;
}

Task::~Task()
{

}
void Task::operator()()
{
    (*m_func_ptr)(m_arg);
}