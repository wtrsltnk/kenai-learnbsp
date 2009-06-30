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

#include "BspObject.h"
#include <string.h>

/* \brief */
int BspObject::sIDCount = 0;

/*
 * \brief
 */
BspObject::BspObject(const char* name, int type)
        : mID(BspObject::sIDCount++), mType(type)
{
    this->mName = new char[strlen(name) + 1];
    strcpy(this->mName, name);
}

/*
 * \brief
 */
BspObject::~BspObject()
{
    delete []this->mName;
}

/*
 * \brief
 * \return
 */
int BspObject::getID()
{
    return this->mID;
}

/*
 * \brief
 * \return
 */
const char* BspObject::getName()
{
    return this->mName;
}

/*
 * \brief 
 * \return 
 */
int BspObject::getType()
{
    return this->mType;
}
