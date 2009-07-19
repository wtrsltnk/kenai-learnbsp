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

#include "ZipPackage.h"
#include <string.h>

using namespace fs;

ZipPackage::ZipPackage(const char* filename)
    : Package(filename)
{
    this->mFile = unzOpen(filename);
}

ZipPackage::~ZipPackage()
{
    delete []this->mPackagename;
    unzClose(this->mFile);
}

bool ZipPackage::isOpen()
{
    return (this->mFile != NULL);
}

const char* ZipPackage::findFile(const char* filename)
{
    char* result = NULL;
    if (unzGoToFirstFile(this->mFile) == UNZ_OK)
    {
        do
        {
            if (unzOpenCurrentFile(this->mFile) == UNZ_OK)
            {
                unz_file_info info;
                unzGetCurrentFileInfo(this->mFile, NULL, this->mFindbuffer, 512, NULL, 0, NULL, 0);
                if (strstr(this->mFindbuffer, filename) != NULL)
                {
                    result = this->mFindbuffer;
                }
                unzCloseCurrentFile(this->mFile);
            }
        }
        while (unzGoToNextFile(this->mFile) == UNZ_OK && result == NULL);
        
    }
    return result;
}

bool ZipPackage::openFile(Data& data, const char* filename)
{
    bool result = true;

    if (unzLocateFile(this->mFile, filename, 2) == UNZ_OK)
    {
        if (unzOpenCurrentFile(this->mFile) == UNZ_OK)
        {
            unz_file_info info;
            unzGetCurrentFileInfo(this->mFile, &info, NULL, 0, NULL, 0, NULL, 0);

            data.dataSize = info.uncompressed_size;
            data.data = new unsigned char[data.dataSize];
            data.name = new char[strlen(filename) + 1];
            strcpy(data.name, filename);
            if (unzReadCurrentFile(this->mFile, data.data, data.dataSize) != data.dataSize)
                result = false;
            unzCloseCurrentFile(this->mFile);
        }
    }

    return result;
}
