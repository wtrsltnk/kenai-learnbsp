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

#include "BspPluginContext.h"
#include <map>
#include <string>

/*!
 * \brief
 */
class BspObject
{
public:
    BspObject(BspPluginContext& context, const char* name, int type);
    virtual ~BspObject();

    int getID() const;
    const char* getName() const;
    int getType() const;
    const float* getOrigin() const;

    virtual void render(double time) = 0;
    virtual BspObject* createInstance(const std::map<std::string, std::string>& entityKeys, BspPluginContext& context) = 0;
    virtual const BspMesh* getMesh() const = 0;

protected:
    /*! \brief */
    float mOrigin[3];
    /*! \brief */
    BspPluginContext& mContext;
    
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

