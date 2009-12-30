#ifndef _THREAD_H
#define	_THREAD_H

#include <GL/glfw.h>

/*
 * \brief
 */
class Mutexer
{
public:
    /*
     * \brief
     * \param mutex
     */
    Mutexer(GLFWmutex& mutex) : mMutex(mutex)
    {
        glfwLockMutex(mMutex);
    }

    /*
     * \brief
     */
    virtual ~Mutexer()
    {
        glfwUnlockMutex(mMutex);
    }

    static GLFWmutex createMutex()
    {
        return glfwCreateMutex();
    }

    static void destroyMutex(GLFWmutex mutex)
    {
        glfwDestroyMutex(mutex);
    }

private:
    /* \brief */
    GLFWmutex& mMutex;
};

/*
 * \brief
 */
class Thread
{
public:
    virtual ~Thread();

    void execute();

protected:
    virtual void run() = 0;

private:
    /* \brief */
    GLFWthread mThread;

private:
    static void staticRun(void* ptr);

};

#endif	/* _THREAD_H */

