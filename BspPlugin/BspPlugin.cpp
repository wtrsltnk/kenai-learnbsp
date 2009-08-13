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

#include "BspPlugin.h"
#include <string.h>

/*!
 * \brief
 * \param name
 */
BspPlugin::BspPlugin(const char* name, BspPluginContext* context)
    : mContext(context)
{
    this->mName = new char[strlen(name) + 1];
    strcpy(this->mName, name);
}

/*!
 * \brief
 */
BspPlugin::~BspPlugin()
{
    delete []this->mName;
    while (!this->mObjectTypes.empty())
    {
        BspObject* obj = this->mObjectTypes.back();
        delete obj;
        this->mObjectTypes.pop_back();
    }
    while (!this->mInstances.empty())
    {
        BspObject* obj = this->mInstances.back();
        delete obj;
        this->mInstances.pop_back();
    }
}

/*!
/ * \brief
 * \return
 */
const char* BspPlugin::getName() const
{
    return this->mName;
}

/*!
 * \brief
 * \param object
 */
void BspPlugin::addObjectType(BspObject* object)
{
    this->mObjectTypes.push_back(object);
}

/*!
 * \brief
 * \param name
 * \return
 */
bool BspPlugin::hasInstance(const char* name) const
{
    for (std::vector<BspObject*>::const_iterator itr = this->mObjectTypes.begin(); itr != this->mObjectTypes.end(); ++itr)
    {
        BspObject* object = *itr;
        if (strcasecmp(object->getName(), name) == 0)
            return true;
    }
    return false;
}

/*!
 * \brief
 * \param name
 * \return
 */
BspObject* BspPlugin::getInstance(const char* name, const std::map<std::string, std::string>& entityKeys)
{
    for (std::vector<BspObject*>::const_iterator itr = this->mObjectTypes.begin(); itr != this->mObjectTypes.end(); ++itr)
    {
        BspObject* object = *itr;
        if (strcasecmp(object->getName(), name) == 0)
        {
            BspObject* instance = object->createInstance(entityKeys, *this->mContext);
            this->mInstances.push_back(instance);
            return instance;
        }
    }
    return NULL;
}


