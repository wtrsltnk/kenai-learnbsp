/* 
 * File:   Plugin.cpp
 * Author: wouter
 * 
 * Created on July 21, 2009, 8:53 PM
 */

#include "Plugin.h"
#include <stdlib.h>

Plugin::Plugin()
    : BspPlugin("Basics")
{
}

Plugin::~Plugin()
{
}

bool Plugin::hasInstance(const char* name) const
{
    return false;
}

BspObject* Plugin::getInstance(const char* name) const
{
    return NULL;
}

extern "C" BspPlugin* createPlugin()
{
    return new Plugin();
}

extern "C" void destroyPlugin(BspPlugin* plugin)
{
    if (plugin != NULL)
        delete plugin;
}
