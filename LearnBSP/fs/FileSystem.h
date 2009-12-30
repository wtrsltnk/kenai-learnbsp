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

#ifndef _FILESYSTEM_H
#define	_FILESYSTEM_H

#include "../common/data.h"
#include "../fs/image/texture.h"
#include <vector>

namespace fs
{

class File;
class Package;
class Resource;
typedef std::vector<File*> FileList;
typedef std::vector<Package*> PackageList;
typedef std::vector<Resource*> ResourceList;

/*!
 * \brief
 */
class FileSystem
{
public:
    FileSystem(const char* root);
    virtual ~FileSystem();

    virtual bool addPackage(const char* filename);
    virtual const char* findFile(const char* name);
    virtual bool openFile(Data& data, const char* filename);
    virtual bool openTexture(Texture& texture, const char* filename);
    virtual bool openTexture(Texture& texture, const Data& data, const char* packageName = NULL);
    virtual Resource* openResource(const char* filename);

protected:
    /*! \brief */
    char fileSystemRoot[256];
    /*! \brief */
    FileList files;
    /*! \brief */
    PackageList packages;
    /*! \brief */
    ResourceList resources;
    /*! \brief */
    char findName[256];

    Package* getPackage(const char* name);
    File* getFile(const char* name);
    const char* getPackageName(const char* filename);
    const char* getFileName(const char* filename);

    static bool findFileInFolder(const char* folder, const char* file, char* result);

};

}

#endif	/* _FILESYSTEM_H */

