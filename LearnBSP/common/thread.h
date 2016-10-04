#ifndef _THREAD_H
#define	_THREAD_H

#include <thread>
#include <mutex>

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
    Mutexer(std::mutex& mutex) : mMutex(mutex)
    {
        this->mMutex.lock();
    }

    /*
     * \brief
     */
    virtual ~Mutexer()
    {
        this->mMutex.unlock();
    }

private:
    /* \brief */
    std::mutex& mMutex;
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
    std::thread mThread;

private:
    static void staticRun(void* ptr);

};

#endif	/* _THREAD_H */

