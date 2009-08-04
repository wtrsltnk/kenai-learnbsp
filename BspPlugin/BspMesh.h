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

#ifndef _BSPMESH_H
#define	_BSPMESH_H

#include <map>
#include <string>

/*!
 * \brief
 */
class BspMesh
{
public:
    BspMesh();
    virtual ~BspMesh();

    /*! \brief */
    virtual bool collides(float start[3], float end[3]) const = 0;
    /*! \brief */
    virtual void update(double time) = 0;
    /*! \brief */
    virtual void render() const = 0;
    
    /*! \brief */
    void setSolid(bool solid);
    /*! \brief */
    bool isSolid() const;

    void setFxMode(int mode);
    int getFxMode() const;

    void setFxColor(float color[3]);
    const float* getFxColor() const;

    void setFxAmount(float amount);
    float getFxAmount() const;

    const float* getMins() const;
    const float* getMaxs() const;

    void setEntity(const std::map<std::string, std::string>& entityKeys);

protected:
    void setupShader() const;

    /*! \brief */
    bool mIsSolid;
    /*! \brief */
    int mFxMode;
    /*! \brief */
    float mFxColor[3];
    /*! \brief */
    float mFxAmount;
    /*! \brief */
    float mMins[3];
    /*! \brief */
    float mMaxs[3];

    
};

#endif	/* _BSPMESH_H */

