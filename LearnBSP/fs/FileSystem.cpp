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
#include "Resource.h"
#include "../HlBspData.h"
#include "../Q3BspData.h"
#include "../common/common.h"
#include "mesh/Mdl.h"
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>

using namespace fs;

FileSystem::FileSystem(const char* root)
{
    Common::stringCopy(this->fileSystemRoot, root);
}

FileSystem::~FileSystem()
{
	while (this->resources.empty() == false)
	{
		Resource* resource = this->resources.back();
		this->resources.pop_back();
		delete resource;
	}

	while (this->files.empty() == false)
	{
		File* file = this->files.back();
		this->files.pop_back();
		delete file;
	}

	while (this->packages.empty() == false)
	{
		Package* package = this->packages.back();
		this->packages.pop_back();
		delete package;
	}
}

bool FileSystem::addPackage(const char* filename)
{
    const char* ext = Common::getExtention(filename);
    const char* fullpath = findFile(filename);

    if (fullpath == NULL)
        return false;
    
    if (Common::stringCompare(ext, ".wad") == 0)
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
	else if (Common::stringCompare(ext, ".zip") == 0 && Common::stringCompare(ext, ".pk3") == 0)
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
    if (FileSystem::findFileInFolder(fileSystemRoot, name, findName))
        return findName;
	
    for (PackageList::iterator package = this->packages.begin(); package != this->packages.end(); ++package)
    {
        const char* found = (*package)->findFile(name);

        if (found != NULL)
        {
            sprintf(findName, "%s@%s", (*package)->getPackagename(), found);
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
        return openTexture(texture, file, getPackageName(filename));
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
        const char* ext = Common::getExtention(packageName);
        if (Common::stringCompare(ext, ".wad") == 0)
        {
            return openMiptex(texture, data);
        }
    }
    const char* ext = Common::getExtention(data.name);

    if (Common::stringCompare(ext, ".tga") == 0)
    {
        result = openTarga(texture, data);
    }
    else if (Common::stringCompare(ext, ".bmp") == 0)
    {
        result = openBitmap(texture, data);
    }
//    else if (Common::stringCompare(ext, ".jpg") == 0)
//    {
//        result = openJpeg(texture, data);
//    }
//    else if (Common::stringCompare(ext, ".png") == 0)
//    {
//        result = openPng(texture, data);
//    }
    return result;
}

Resource* FileSystem::openResource(const char* name)
{
	const char* find = name;

	if (Common::fileExists(name) == false)
		find = this->findFile(name);

	if (find == NULL)
		return NULL;
	
    const char* ext = Common::getExtention(find);

	for (ResourceList::iterator itr = this->resources.begin(); itr != this->resources.end(); ++itr)
		if (Common::stringCompare((*itr)->getFilename(), find) == 0)
			return (*itr);

	Data file;
	if (this->openFile(file, find))
	{
		Resource* result = NULL;

        const char* packageName = this->getPackageName(find);
		if (packageName != NULL)
		{
			const char* ext = Common::getExtention(packageName);
			if (Common::stringCompare(ext, ".wad") == 0)
			{
				Texture* texture = new Texture(find);
				if (openMiptex(*texture, file) == false)
				{
					delete texture;
					return NULL;
				}
				result = texture;
			}
		}
		else if (Common::stringCompare(ext, ".tga") == 0)
		{
			Texture* texture = new Texture(find);
			if (openTarga(*texture, file) == false)
			{
				delete texture;
				return NULL;
			}
			result = texture;
		}
		else if (Common::stringCompare(ext, ".bmp") == 0)
		{
			Texture* texture = new Texture(find);
			if (openBitmap(*texture, file) == false)
			{
				delete texture;
				return NULL;
			}
			result = texture;
		}
//		else if (Common::stringCompare(ext, ".jpg") == 0)
//		{
//			Texture* texture = new Texture(find);
//			if (openJpeg(*texture, file) == false)
//			{
//				delete texture;
//				return NULL;
//			}
//			result = texture;
//		}
//		else if (Common::stringCompare(ext, ".png") == 0)
//		{
//			Texture* texture = new Texture(find);
//			if (openPng(*texture, file) == false)
//			{
//				delete texture;
//				return NULL;
//			}
//			result = texture;
//		}
		else if (Common::stringCompare(ext, ".mdl") == 0)
		{
			result = new Mdl(file, *this);
		}
		else if (Common::stringCompare(ext, ".bsp") == 0)
		{
			if (HlBspData::testBSP(file))
				result = new HlBspData(file);
			else if (Q3BspData::testBSP(file))
				result = new Q3BspData(file);
		}

		if (result != NULL)
			this->resources.push_back(result);
		
		return result;
	}
	return NULL;
}

Package* FileSystem::getPackage(const char* name)
{
    for (PackageList::iterator itr = this->packages.begin(); itr != this->packages.end(); ++itr)
        if (Common::stringCompare((*itr)->getPackagename(), name) == 0)
            return *itr;
    
    return NULL;
}

File* FileSystem::getFile(const char* name)
{
    for (FileList::iterator itr = this->files.begin(); itr != this->files.end(); ++itr)
        if (Common::stringCompare((*itr)->name, name) == 0)
            return *itr;
    
    return NULL;
}

const char* FileSystem::getPackageName(const char* filename)
{
    static char packageName[256] = { 0 };
    const char* split = Common::stringSplit(filename, "@");

    Common::memorySet(packageName, 0, 256);
    if (split != NULL)
    {
        Common::stringCopy(packageName, filename, split - filename);
        return packageName;
    }
    return NULL;
}

const char* FileSystem::getFileName(const char* filename)
{
    const char* split = Common::stringSplit(filename, "@");

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
            if (Common::stringCompare(item->d_name, ".") == 0 || Common::stringCompare(item->d_name, "..") == 0 || Common::stringCompare(item->d_name, ".svn") == 0)
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
				Common::stringFormat(newFolder, "%s/%s", folder, item->d_name);
                if (FileSystem::findFileInFolder(newFolder, file, result))
                {
                    found = true;
                    break;
                }
            }
            else
            {
                if (Common::stringCompare(item->d_name, file, Common::stringLength(file)) == 0)
                {
					Common::stringFormat(result, "%s/%s", folder, item->d_name);
                    found = true;
                    break;
                }
            }
        }
        closedir(dir);
    }
    return found;
}
