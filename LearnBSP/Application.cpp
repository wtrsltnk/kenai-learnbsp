#include "Application.h"
#include "common/math3d.h"
#include <stdio.h>

/* \brief */
Application* Application::sCurrent = NULL;

/*
 * \brief 
 * \param key
 * \param action
 */
void Application::staticKeyPressed(int key, int action)
{
    if (Application::sCurrent != NULL)
        Application::sCurrent->keyPressed(key, action);
}

/*
 * \brief
 * \param width
 * \param height
 */
Application::Application(int width, int height)
        : mWidth(width ? width : 1), mHeight(height ? height : 1), mResult(-1), mRunning(true), mSpeed(50.0f)
{
    Application::sCurrent = this;
    glfwInit();
}

/*
 * \brief
 */
Application::~Application()
{
    glfwTerminate();
}

/*
 * \brief
 * \param title
 * \return 
 */
bool Application::openWindow(const char* title)
{
    if (glfwOpenWindow(mWidth, mHeight, 8, 8, 8, 8, 24, 0, GLFW_WINDOW))
    {
        glfwSetWindowTitle(title);
        glfwSetKeyCallback(Application::staticKeyPressed);
        return this->initialize();
    }
    return false;
}

/*
 * \brief
 */
void Application::run()
{
    if (this->openWindow("Application"))
    {
        double time = glfwGetTime();
        double prevTime = time;
        int fps = 0;

        do
        {
            fps++;
            double newTime = glfwGetTime();
            double timeDiff = newTime - prevTime;
            prevTime = newTime;
            if ((newTime - time) > 1)
            {
                mFPS = double(fps) / (newTime - time);
                char str[128];
                sprintf(str, "FPS: %f", mFPS);
                glfwSetWindowTitle(str);
                fps = 0;
                time = newTime;
            }

            if (glfwGetKey('W'))
                mCamera.MoveLocal(-mSpeed * timeDiff, 0, 0);
            if (glfwGetKey('S'))
                mCamera.MoveLocal(mSpeed * timeDiff, 0, 0);

            if (glfwGetKey('A'))
                mCamera.MoveLocal(0, -mSpeed * timeDiff, 0);
            if (glfwGetKey('D'))
                mCamera.MoveLocal(0, mSpeed * timeDiff, 0);

            int mx, my;
            float rot[3] = { 0 };
            glfwGetMousePos(&mx, &my);

            // Now the rotatins do not depent on the speed of rendering
            rot[2] = ((float(mx) / mWidth) * M_PI - M_PI_2) * 4.0f;
            rot[0] = -90.0f + (float(my) / mHeight) * M_PI - M_PI_2;

            mCamera.SetRotation(rot);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            render(newTime);

            glfwSwapBuffers();

            this->mRunning = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
        }
        while (this->mRunning);
        this->mResult = 0;
    }
}
/*
 * \brief
 * \return
 */
int Application::cleanup()
{
    this->destroy();
    
    return this->mResult;
}

/*
 * \brief
 * \return 
 */
bool Application::initialize()
{
    glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
    return true;
}

/*
 * \brief
 * \param time
 */
void Application::render(double time)
{
}

/*
 * \brief
 */
void Application::destroy()
{
}

/*
 * \brief 
 * \param key
 * \param action
 */
void Application::keyPressed(int key, int action)
{
}
