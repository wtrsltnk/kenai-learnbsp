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

#include "FileSystem.h"
#include "ZipPackage.h"
#include "WadPackage.h"
#include "File.h"
#include "image/image.h"
#include "FileSystemException.h"

#include <string.h>
#include <iostream>
#include <dirent.h>

using namespace fs;

FileSystem::FileSystem(const char* gameRoot)
{
    strcpy(this->gameRoot, gameRoot);
//
//    DIR* dir = opendir(gameRoot);
//
//    if (dir != NULL)
//    {
//        struct dirent *item;
//        while ((item = readdir(dir)) != 0)
//        {
//            if (strcmp(item->d_name, ".") == 0 || strcmp(item->d_name, "..") == 0)
//                continue;
//
//            if (item->d_type != 4)	// !FOLDER
//            {
//                char* ext = item->d_name + (strlen(item->d_name) - 4);
//                if (strcasecmp(ext, ".zip") == 0)
//                {
//                    char fullpath[256] = { 0 };
//                    sprintf(fullpath, "%s/%s", gameRoot, item->d_name);
//                    this->packages.push_back(new ZipPackage(fullpath));
//                }
////                else if (strcasecmp(ext, ".wad") == 0)                           // Only add wad's that are neede by the bsp file
////                {
////                    char fullpath[256] = { 0 };
////                    sprintf(fullpath, "%s/%s", gameRoot, item->d_name);
////                    this->packages.push_back(new WadPackage(fullpath));
////                }
//            }
//        }
//        closedir(dir);
//    }
}

FileSystem::~FileSystem()
{
}

bool FileSystem::addPackage(const char* filename)
{
    const char* ext = strrchr(filename, '.');
    const char* fullpath = findFile(filename);

    if (fullpath == NULL)
        return false;
    
    if (strcasecmp(ext, ".wad") == 0)
    {
        try
        {
            WadPackage* package = new WadPackage(fullpath);
            this->packages.push_back(package);
        }
        catch (const FileSystemException& error)
        {
            std::cout << error.getMessage() << std::endl;
            return false;
        }
    }
    else if (strcasecmp(ext, ".zip") == 0)
    {
        try
        {
            ZipPackage* package = new ZipPackage(fullpath);
            this->packages.push_back(package);
        }
        catch (const FileSystemException& error)
        {
            std::cout << error.getMessage() << std::endl;
            return false;
        }
    }
    return true;
}

const char* FileSystem::findFile(const char* name)
{
    if (FileSystem::findFileInFolder(gameRoot, name, findName))
    {
        return findName;
    }
    for (PackageList::iterator itr = this->packages.begin(); itr != this->packages.end(); ++itr)
    {
        const char* found = (*itr)->findFile(name);

        if (found != NULL)
        {
            sprintf(findName, "%s@%s", (*itr)->getPackagename(), found);
            return findName;
        }
    }
    return NULL;
}

bool FileSystem::openFile(Data& data, const char* filename)
{
    if (filename == NULL)
        return false;
    
    File* file = this->getFile(filename);
    if (file == NULL)
    {
        const char* packageName = this->getPackageName(filename);
        const char* fileInPackage = this->getFileName(filename);

        if (packageName != NULL)
        {
            Package* package = this->getPackage(packageName);
            if (package != NULL)
                return package->openFile(data, fileInPackage);
        }
        else
        {
            try
            {
                file = new File(filename);
                files.push_back(file);
                data.copyFrom(*file);
            }
            catch (const char* err)
            {
                std::cout << "Error opening file: " << err << std::endl;
                delete file;
                return false;
            }
        }
    }
    else
        data.copyFrom(*file);
    
    return true;
}

bool FileSystem::openTexture(Texture& texture, const char* filename)
{
    if (filename == NULL)
        return false;

    Data file;

    if (openFile(file, filename))
    {
        const char* packageName = getPackageName(filename);
        return openTexture(texture, file, packageName);
    }

    return false;
}

bool FileSystem::openTexture(Texture& texture, const Data& data, const char* packageName)
{
    bool result = false;
    if (data.name == NULL)
        return false;

    if (packageName != NULL)
    {
        const char* ext = strrchr(packageName, '.');
        if (strcasecmp(ext, ".wad") == 0)
        {
            return openMiptex(texture, data);
        }
    }
    const char* ext = strrchr(data.name, '.');

    if (strcasecmp(ext, ".tga") == 0)
    {
        result = openTarga(texture, data);
    }
    else if (strcasecmp(ext, ".bmp") == 0)
    {
        result = openBitmap(texture, data);
    }
    else if (strcasecmp(ext, ".jpg") == 0)
    {
        result = openJpeg(texture, data);
    }
    else if (strcasecmp(ext, ".png") == 0)
    {
        result = openPng(texture, data);
    }
    return result;
}

Package* FileSystem::getPackage(const char* name)
{
    for (PackageList::iterator itr = this->packages.begin(); itr != this->packages.end(); ++itr)
        if (strcasecmp((*itr)->getPackagename(), name) == 0)
            return *itr;
    
    return NULL;
}

File* FileSystem::getFile(const char* name)
{
    for (FileList::iterator itr = this->files.begin(); itr != this->files.end(); ++itr)
        if (strcasecmp((*itr)->name, name) == 0)
            return *itr;
    
    return NULL;
}

const char* FileSystem::getPackageName(const char* filename)
{
    static char packageName[256] = { 0 };
    const char* split = strstr(filename, "@");

    memset(packageName, 0, 256);
    if (split != NULL)
    {
        strncpy(packageName, filename, split - filename);
        return packageName;
    }
    return NULL;
}

const char* FileSystem::getFileName(const char* filename)
{
    const char* split = strstr(filename, "@");

    if (split != NULL)
    {
        return (split + 1);
    }
    return filename;
}

bool FileSystem::findFileInFolder(const char* folder, const char* file, char* result)
{
    bool found = false;
    DIR* dir = opendir(folder);

    if (dir != 0)
    {
        struct dirent *item;
        while ((item = readdir(dir)) != 0)
        {
            if (strcmp(item->d_name, ".") == 0 || strcmp(item->d_name, "..") == 0 || strcmp(item->d_name, ".svn") == 0)
                continue;

#ifdef WIN32
			struct stat stat_base;
            stat(item->d_name, &stat_base);
            if (stat_base.st_mode == S_IFDIR)
#else
            if (item->d_type == 4)	// FOLDER
#endif
			{
                char newFolder[256] = { 0 };
                strcpy(newFolder, folder);
                strcat(newFolder, "/");
                strcat(newFolder, item->d_name);
                if (FileSystem::findFileInFolder(newFolder, file, result))
                {
                    found = true;
                    break;
                }
            }
            else
            {
                if (strcasecmp(item->d_name, file) == 0)
                {
                    strcpy(result, folder);
                    strcat(result, "/");
                    strcat(result, item->d_name);
                    found = true;
                    break;
                }
            }
        }
        closedir(dir);
    }
    return found;
}
