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

#include "Plugin.h"
#include "Wall.h"
#include "Illusionary.h"
#include "Breakable.h"
#include <string.h>

/*!
 * \brief
 * \param contex
 */
Plugin::Plugin(BspPluginContext* context)
    : BspPlugin("Basics", context)
{
    this->mObjects.push_back(new Wall(*context, "func_wall"));
    this->mObjects.push_back(new Illusionary(*context, "func_illusionary"));
    this->mObjects.push_back(new Breakable(*context, "func_breakable"));
}

/*!
 * \brief
 */
Plugin::~Plugin()
{
    while (!this->mObjects.empty())
    {
        BspObject* obj = this->mObjects.back();
        delete obj;
        this->mObjects.pop_back();
    }
    while (!this->mInstances.empty())
    {
        BspObject* obj = this->mInstances.back();
        delete obj;
        this->mInstances.pop_back();
    }
}

/*!
 * \brief
 * \param name
 * \return
 */
bool Plugin::hasInstance(const char* name) const
{
    for (std::vector<BspObject*>::const_iterator itr = this->mObjects.begin(); itr != this->mObjects.end(); ++itr)
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
BspObject* Plugin::getInstance(const char* name, const std::map<std::string, std::string>& entityKeys)
{
    for (std::vector<BspObject*>::const_iterator itr = this->mObjects.begin(); itr != this->mObjects.end(); ++itr)
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

/*!
 * \brief
 * \param context
 * \return
 */
extern "C" BspPlugin* createPlugin(BspPluginContext* context)
{
    return new Plugin(context);
}

/*!
 * \brief
 * \param plugin
 */
extern "C" void destroyPlugin(BspPlugin* plugin)
{
    if (plugin != NULL)
        delete plugin;
}
