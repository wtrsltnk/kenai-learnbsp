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

#include "WadPackage.h"
#include "FileSystemException.h"
#include <string.h>

using namespace fs;

WadPackage::WadPackage(const char* filename)
    : Package(filename)
{
    this->mFile = fopen(filename, "rb");
    if (this->mFile != NULL)
    {
        fread(&this->mHeader, 1, sizeof(tWADHeader), this->mFile);
        this->mLumps = new tWADLump[this->mHeader.lumpsCount];
        fseek(this->mFile, this->mHeader.lumpsOffset, SEEK_SET);
        fread(this->mLumps, this->mHeader.lumpsCount, sizeof(tWADLump), this->mFile);
    }
    else
    {
        throw FileSystemException("Cannot open %s", filename);
    }
}

WadPackage::~WadPackage()
{
    if (this->mFile != NULL)
    {
        fclose(this->mFile);
    }
}

const char* WadPackage::findFile(const char* filename)
{
    for (int i = 0; i < this->mHeader.lumpsCount; i++)
    {
        tWADLump& lump = this->mLumps[i];
        if (strcasecmp(lump.name, filename) == 0)
        {
            return this->mLumps[i].name;
        }
    }
    return NULL;
}

bool WadPackage::openFile(Data& data, const char* filename)
{
    for (int i = 0; i < this->mHeader.lumpsCount; i++)
    {
        const tWADLump& lump = this->mLumps[i];
        if (strcasecmp(lump.name, filename) == 0)
        {
            if (data.name != NULL)
                delete []data.name;
            data.name = new char[strlen(filename) + 1];
            strcpy(data.name, filename);
            
            data.dataSize = lump.size;

            if (data.data != NULL)
                delete []data.data;
            data.data = new unsigned char[data.dataSize];
            if (data.data == NULL)
                return false;
            
            fseek(this->mFile, lump.offset, SEEK_SET);
            return (fread(data.data, 1, lump.size, this->mFile) == lump.size);
        }
    }
    return false;
}
