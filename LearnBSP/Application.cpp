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
        : mWidth(800), mHeight(600), mResult(-1), mRunning(true), mSpeed(500.0f), mWorld(NULL), mMap(NULL)
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
			glfwSetWindowTitle(this->mMap);
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
	BspLoader loader(this->mFileSystem);

	if (this->mWorld = loader.loadWorld(Common::getFilename(this->mMap)))
	{
        this->mWorld->setCamera(&this->mCamera);
        this->mWorld->setupEntities(*this->mFileSystem);
        this->setPerspective(45.0f, 0.1f, 4096);
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

/*!
 * \brief Render one frame of the application
 * \param time The current time of the framestart
 */
void Application::render(double time)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    this->mCamera.Update();

    if (this->mWorld != NULL) this->mWorld->render();
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
	if (key == 32 && action == 1)
	{
		if (this->mWorld != NULL)
		{
			this->mWorld->shoot();
		}
	}
//	std::cout << key << " " << action << std::endl;
}

/*!
 * \brief
 * \param title The title of the window
 * \return true means that the window is opened and initialization went OK.
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
                glfwSetWindowTitle(str);
                fps = 0;
                time = newTime;
            }

            this->mCamera.resetChanged();
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

            render(newTime);

            glfwSwapBuffers();

            this->mRunning = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
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
void Application::staticKeyPressed(int key, int action)
{
    if (Application::sCurrent != NULL)
        Application::sCurrent->keyPressed(key, action);
}
