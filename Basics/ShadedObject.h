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

#ifndef _SHADEDOBJECT_H
#define	_SHADEDOBJECT_H

#include <BspObject.h>
#include <map>
#include <string>

/*!
 * \brief
 */
class ShadedObject : public BspObject
{
public:
    ShadedObject(BspPluginContext& context, const char* name, int type);
    virtual ~ShadedObject();

    void setShading(const std::map<std::string, std::string>& entityKeys);

    void setFxMode(int mode);
    int getFxMode() const;

    void setFxColor(float color[3]);
    const float* getFxColor() const;

    void setFxAmount(float amount);
    float getFxAmount() const;
    
protected:
    void setupShader() const;

    /*! \brief */
    int mFxMode;
    /*! \brief */
    float mFxColor[3];
    /*! \brief */
    float mFxAmount;

};

#endif	/* _SHADEDOBJECT_H */

