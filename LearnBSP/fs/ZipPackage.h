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

#ifndef _ZIPPACKAGE_H
#define	_ZIPPACKAGE_H

#include "Package.h"
#include "../common/data.h"
#include "zip/unzip.h"

namespace fs
{

/*!
 * \brief
 */
class ZipPackage : public Package
{
public:
    ZipPackage(const char* filename);
    virtual ~ZipPackage();

    bool isOpen();
    const char* findFile(const char* filename);
    bool openFile(Data& data, const char* filename);

private:
    /*! \brief */
    char* mPackagename;
    /*! \brief */
    unzFile mFile;
    /*! \brief */
    char mFindbuffer[512];
    
};

}

#endif	/* _ZIPPACKAGE_H */

