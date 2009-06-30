#include "thread.h"

/*
 * \brief
 */
Thread::~Thread()
{
}

/*
 * \brief
 */
void Thread::execute()
{
    this->mThread = glfwCreateThread(Thread::staticRun, this);
}

/*
 * \brief
 * \param ptr
 */
void Thread::staticRun(void* ptr)
{
    Thread* thread = (Thread*) ptr;

    if (thread != NULL)
        thread->run();
}