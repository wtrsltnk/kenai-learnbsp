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

#ifndef _WADPACKAGE_H
#define	_WADPACKAGE_H

#include "Package.h"
#include "../common/data.h"
#include <stdio.h>

namespace fs
{

/*!
 * \brief
 */
typedef struct sWADHeader
{
    char signature[4];
    int lumpsCount;
    int lumpsOffset;

} tWADHeader;

/*!
 * \brief
 */
typedef struct sWADLump
{
    int offset;
    int sizeOnDisk;
    int size;
    char type;
    char compression;
    char empty0;
    char empty1;
    char name[16];

} tWADLump;

/*!
 * \brief
 */
class WadPackage : public Package
{
public:
    WadPackage(const char* filename);
    virtual ~WadPackage();

    virtual const char* findFile(const char* filename);
    virtual bool openFile(Data& data, const char* filename);

private:
    /*! \brief */
    char* mPackagename;
    /*! \brief */
    FILE* mFile;
    /*! \brief */
    tWADHeader mHeader;
    /*! \brief */
    tWADLump* mLumps;
    /*! \brief */
    char mFindbuffer[512];

};

}

#endif	/* _WADPACKAGE_H */

