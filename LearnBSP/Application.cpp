/*
 * Learn BSP is a sample source code to see how a Half-Life level file
 * can be used in your 3D application
 * Copyright (C) 2009  Wouter Saaltink

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define GLEXTL_IMPLEMENTATION
#include <GL/glextl.h>

#include "Application.h"
#include "common/math3d.h"
#include "common/common.h"
#include "BspLoader.h"
#include <iostream>

/*!
 * \brief
 * \param width The width of the window created for this Application
 * \param height The height of the window created for this Application
 */
Application::Application(int argc, char* argv[])
        : mWidth(800), mHeight(600), mResult(-1), mRunning(true), mSpeed(500.0f), mWorld(NULL), mMap(NULL), mConsole(NULL), mShowConsole(true)
{
    Application::sCurrent = this;
    glfwInit();

	/// ToDo: fix this gameroot stuff, now it will not work when you give a gameroot and a mapname with fullpath
	char gameroot[256] = { 0 };
	bool foundGameroot = false;
	for (int i = 0; i < argc; i++)
	{
		if (Common::stringCompare(argv[i], "-gameroot") == 0 && argc > i)
		{
			Common::stringCopy(gameroot, argv[i + 1]);
			std::cout << "Game root: " << gameroot << std::endl;
			foundGameroot = true;
		}
	}
	if (argc > 1)
	{
		const char* ext = Common::getExtention(argv[argc - 1]);
		if (Common::stringCompare(ext ,".bsp") == 0)
		{
			this->mMap = argv[argc - 1];
			std::cout << "Map: " << this->mMap << std::endl;
//			glfwSetWindowTitle(this->mMap);
		}
	}
	
	if (foundGameroot == false)
	{
		Common::stringCopy(gameroot, this->mMap);
		int i = Common::stringLength(gameroot);
		char tmp[256] = { 0 };
		while (foundGameroot == false || i <= 0)
		{
			/// Find the last slash
			while (gameroot[i] != '/' && i > 0)
				i--;
			gameroot[i] = '\0';
			Common::stringFormat(tmp, "%s/hl.exe", gameroot);
			if (Common::fileExists(tmp))
			{
				foundGameroot = true;
			}
		}
	}
    this->mFileSystem = new fs::FileSystem(gameroot);
}

/*!
 * \brief
 */
Application::~Application()
{
	if (this->mWorld != NULL)
		delete this->mWorld;
    delete this->mFileSystem;
    glfwTerminate();
}

/*!
 * \brief Initialize the application
 * \return true when initialization went OK
 *
 * The initialization done here is the resources that are neede for the
 * application to run.
 *
 */
bool Application::initialize()
{
	this->mConsole = new Console(this->mWidth, this->mHeight);
	
	BspLoader loader(this, this->mFileSystem);

	loader.setFilename(Common::getFilename(this->mMap));
	loader.run();
	if (this->mWorld = loader.getWorld())
	{
        this->mWorld->setCamera(&this->mCamera);
        this->mWorld->setupEntities(*this->mFileSystem);
        this->setPerspective(65.0f, 0.1f, 4096);
    }
    glClearColor(0.4f, 0.6f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);

    return true;
}

void Application::onChange(int type, const char* msg)
{
	if (type == 1)
		this->mConsole->addLine(msg);
}

/*!
 * \brief Render one frame of the application
 * \param time The current time of the framestart
 */
void Application::render(double time)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    this->mCamera.Update();
	
    if (this->mWorld != NULL) this->mWorld->render();

	if (this->mShowConsole)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0f, this->mWidth, this->mHeight, 0.0f, 0.1f, 50.0f);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		this->mConsole->render();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
}

/*!
 * \brief Destroy when the OpenGL end running
 */
void Application::destroy()
{
    if (this->mWorld != NULL)
        delete this->mWorld;
    this->mWorld = NULL;
}

/*!
 * \brief
 * \param key The key number
 * \param action The action of the key press
 */
void Application::keyPressed(int key, int action)
{
    if (key == GLFW_KEY_ESCAPE && action == 1)
	{
		if (this->mShowConsole)
			this->mShowConsole = false;
		else
			this->mRunning = false;
	}
	else if (key == 32 && action == 1)
	{
		if (this->mWorld != NULL)
		{
			this->mWorld->shoot();
		}
	}
    else if (key == GLFW_KEY_LEFT_CONTROL && action == 1)
	{
		this->mShowConsole = !this->mShowConsole;
	}
//	std::cout << key << " " << action << std::endl;
}

/*!
 * \brief
 * \param w The new width
 * \param h The new Height
 */
void Application::resized(int w, int h)
{
	this->mWidth = w;
	this->mHeight = h;
}

/*!
 * \brief
 * \param title The title of the window
 * \return true means that the window is opened and initialization went OK.
 */
bool Application::openWindow(const char* title)
{
    this->mWindow = glfwCreateWindow(mWidth, mHeight, "window", nullptr, nullptr);
    if (this->mWindow != nullptr)
    {
        glfwSetWindowTitle(this->mWindow, title);
        glfwSetKeyCallback(this->mWindow, Application::staticKeyPressed);
        glfwSetWindowSizeCallback(this->mWindow, Application::staticResized);

        return this->initialize();
    }
    return false;
}

#define M_PI 3.141592f
#define M_PI_2 M_PI * 2.0f

/*!
 * \brief Run the application
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
                glfwSetWindowTitle(this->mWindow, str);
                fps = 0;
                time = newTime;
            }

            this->mCamera.resetChanged();
            if (glfwGetKey(this->mWindow, 'W'))
                mCamera.MoveLocal(-mSpeed * float(timeDiff), 0, 0);
            if (glfwGetKey(this->mWindow, 'S'))
                mCamera.MoveLocal(mSpeed * float(timeDiff), 0, 0);

            if (glfwGetKey(this->mWindow, 'A'))
                mCamera.MoveLocal(0, -mSpeed * float(timeDiff), 0);
            if (glfwGetKey(this->mWindow, 'D'))
                mCamera.MoveLocal(0, mSpeed * float(timeDiff), 0);

            double mx, my;
            float rot[3] = { 0 };
            glfwGetCursorPos(this->mWindow, &mx, &my);

            // Now the rotatins do not depent on the speed of rendering
            rot[2] = ((float(mx) / mWidth) * M_PI - M_PI_2) * 4.0f;
            rot[0] = -90.0f + (float(my) / mHeight) * M_PI - M_PI_2;

            mCamera.SetRotation(rot);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            render(newTime);

            glfwSwapBuffers(this->mWindow);
        }
        while (this->mRunning);
        this->mResult = 0;
    }
}

/*!
 * \brief Cleanup all the resources of this application
 * \return The result number for the application, 0 if OK else it returns the error code
 */
int Application::cleanup()
{
    this->destroy();
    
    return this->mResult;
}

/*!
 * \brief
 * \param fieldOfView
 * \param nearClipping
 * \param farClipping
 */
void Application::setPerspective(float fieldOfView, float nearClipping, float farClipping)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fieldOfView, this->mWidth / this->mHeight, nearClipping, farClipping);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*! \brief */
Application* Application::sCurrent = NULL;

/*!
 * \brief
 * \param key The key number
 * \param action The action of the key press
 */
void Application::staticKeyPressed(GLFWwindow* window, int key, int action, int, int)
{
    if (Application::sCurrent != NULL)
        Application::sCurrent->keyPressed(key, action);
}

/*!
 * \brief
 * \param key The key number
 * \param action The action of the key press
 */
void Application::staticResized(GLFWwindow* window, int w, int h)
{
    if (Application::sCurrent != NULL)
        Application::sCurrent->resized(w, h);
}
