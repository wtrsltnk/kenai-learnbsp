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

#ifndef _BSPOBJECT_H
#define	_BSPOBJECT_H

#include <map>
#include <string>
#include "BspMesh.h"

/*!
 * \brief
 */
class ThinkArgs
{
public:
    virtual ~ThinkArgs() {}
};

/*!
 * \brief
 */
class TouchArgs
{
public:
    virtual ~TouchArgs() {}
};

/*!
 * \brief
 */
class BspObject
{
public:
    BspObject(const char* name, int type);
    virtual ~BspObject();

    int getID() const;
    const char* getName() const;
    int getType() const;
    virtual bool isType(const char* type) const = 0;
    const float* getOrigin() const;

    virtual void render(double time) = 0;
    virtual const BspMesh* getMesh() const = 0;
    virtual void onThink(ThinkArgs& args) = 0;
    virtual void onTouch(TouchArgs& args) = 0;

    virtual void preCache() { }
    
protected:
    /*! \brief */
    float mOrigin[3];

    void setNextThink(double time);
    
private:
    /*! \brief */
    int mID;
    /*! \brief */
    char* mName;
    /*! \brief */
    int mType;
    /*! \brief */
    static int sIDCount;

};

#endif	/* _BSPOBJECT_H */

