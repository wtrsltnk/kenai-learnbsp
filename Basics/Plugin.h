/* 
 * File:   Plugin.h
 * Author: wouter
 *
 * Created on July 21, 2009, 8:53 PM
 */

#ifndef _PLUGIN_H
#define	_PLUGIN_H

#include <BspPlugin.h>

class Plugin : public BspPlugin
{
public:
    Plugin();
    virtual ~Plugin();

    virtual bool hasInstance(const char* name) const;
    virtual BspObject* getInstance(const char* name) const;

private:

};

#endif	/* _PLUGIN_H */

