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

#ifndef _CAMERA_H
#define	_CAMERA_H

/*!
 * \brief
 */
class Camera
{
public:
    Camera();
    virtual ~Camera();
    
    void Update();
    
    void SetPosition(float position[3]);
    const float* getPosition() const;
    const float* getPreviousPosition() const;

    void SetRotation(float rotation[3]);
    const float* getRotation() const;

    const float* getForwardVector() const;
    const float* getLeftVector() const;
    const float* getUpVector() const;

    void MoveGlobal(float forward, float left, float up);
    void MoveLocal(float forward, float left, float up);

    void resetChanged();
    bool hasChanged() const;

private:
    /*! \brief */
    float rotationMatrix[16];
    /*! \brief */
    float position[3];
    /*! \brief */
    float previousPosition[3];
    /*! \brief */
    float rotation[3];
    /*! \brief */
    bool mHasChanged;
   
};

#endif	/* _CAMERA_H */

