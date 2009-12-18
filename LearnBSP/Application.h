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

#ifndef _APPLICATION_H
#define	_APPLICATION_H

#include "common/camera.h"
#include "common/opengl.h"
#include "HlBspWorld.h"
#include "fs/FileSystem.h"

/*!
 * \brief 
 */
class Application
{
public:
    Application(int width, int height);
    virtual ~Application();

    void run();
    int cleanup();
    
protected:
    virtual bool initialize();
    virtual void render(double time);
    virtual void destroy();
    virtual void keyPressed(int key, int action);
    virtual void setPerspective(float fieldOfView, float nearClipping, float farClipping);

private:
    /*! \brief */
    int mWidth;
    /*! \brief */
    int mHeight;
    /*! \brief */
    int mResult;
    /*! \brief */
    bool mRunning;
    /*! \brief */
    float mSpeed;
    /*! \brief */
    double mFPS;
    /*! \brief */
    Camera mCamera;
    /*! \brief */
    BspWorld* mWorld;
    /*! \brief */
    fs::FileSystem* mFileSystem;

    bool openWindow(const char* title);

    static Application* sCurrent;
    static void staticKeyPressed(int key, int action);

};

#endif	/* _APPLICATION_H */

