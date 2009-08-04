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

#include "PluginManager.h"
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

/*!
 * \brief
 */
PluginManager* PluginManager::sInstance = NULL;

/*!
 * \brief
 * \param binroot
 * \return
 */
PluginManager* PluginManager::createInstance(const char* binroot, BspPluginContext* context)
{
    if (PluginManager::sInstance == NULL)
        PluginManager::sInstance = new PluginManager(binroot, context);

    return PluginManager::sInstance;
}

/*!
 * \brief
 * \return
 */
PluginManager* PluginManager::Instance()
{
    if (PluginManager::sInstance == NULL)
        throw "No instance initialized";
    
    return PluginManager::sInstance;
}

/*!
 * \brief
 */
void PluginManager::destroyInstance()
{
    if (PluginManager::sInstance != NULL)
        delete PluginManager::sInstance;
}

/*!
 * \brief
 * \param binroot
 */
PluginManager::PluginManager(const char* binroot, BspPluginContext* context)
    : mContext(context)
{
    DIR* dir = opendir(binroot);

    if (dir != NULL)
    {
        struct dirent *item;
        while ((item = readdir(dir)) != 0)
        {
            if (strcmp(item->d_name, ".") == 0 || strcmp(item->d_name, "..") == 0)
                continue;

            if (item->d_type != 4)	// !FOLDER
            {
                const char* ext = strrchr(item->d_name, '.');
                if (strcasecmp(ext, ".so") == 0)
                {
                    char fullpath[256] = { 0 };
                    sprintf(fullpath, "%s/%s", binroot, item->d_name);
                    if (this->addPlugin(fullpath))
                    {
                        std::cout << fullpath << " loaded successfully!" << std::endl;
                    }
                    else
                        std::cout << fullpath << " failed to load" << std::endl;
                }
            }
        }
        closedir(dir);
    }
}

/*!
 * \brief
 */
PluginManager::~PluginManager()
{
    while (!this->mPlugins.empty())
    {
        sLoadedPlugin plugin = this->mPlugins.back();
        this->mPlugins.pop_back();

        (*plugin.destroy)(plugin.plugin);
        dlclose(plugin.handle);
    }
}

/*!
 * \brief
 * \param filename
 * \return
 */
bool PluginManager::addPlugin(const char* filename)
{
    tLoadedPlugin plugin = { NULL };
    plugin.handle = dlopen(filename, RTLD_LAZY);

    if (plugin.handle == NULL)
    {
        std::cout << dlerror() << std::endl;
        return false;
    }

    plugin.create = (tCreatePlugin*)dlsym(plugin.handle, "createPlugin");
    plugin.destroy = (tDestroyPlugin*)dlsym(plugin.handle, "destroyPlugin");

    if (plugin.create == NULL || plugin.destroy == NULL)
        return false;

    plugin.plugin = (*plugin.create)(this->mContext);
    this->mPlugins.push_back(plugin);
    
    return true;
}

/*!
 * \brief
 * \param name
 * \return
 */
BspObject* PluginManager::getEntityInstance(const char* name, const std::map<std::string, std::string>& entityKeys)
{
    for (std::vector<tLoadedPlugin>::iterator itr = this->mPlugins.begin(); itr != this->mPlugins.end(); ++itr)
    {
        tLoadedPlugin plugin = *itr;
        if (plugin.plugin != NULL)
        {
            if (plugin.plugin->hasInstance(name))
            {
                return plugin.plugin->getInstance(name, entityKeys);
            }
        }
    }
    return NULL;
}

/*!
 * \brief
 * \return
 */
BspPluginContext* PluginManager::getContext()
{
    return this->mContext;
}
