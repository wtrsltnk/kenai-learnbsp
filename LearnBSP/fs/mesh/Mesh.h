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

#ifndef _MESH_H
#define	_MESH_H

#include "../../common/data.h"
#include "../../fs/FileSystem.h"
#include "../Resource.h"
#include "mdltypes.h"

class Mesh : public fs::Resource
{
public:
    Mesh(Data& file, fs::FileSystem& filesystem);
    virtual ~Mesh();

    void render();

private:
    tMDLHeader* header;
    unsigned char* buffer;

};

#endif	/* _MESH_H */

