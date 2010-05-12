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

#include "File.h"
#include <stdio.h>
#include <string.h>

using namespace fs;

File::File(const char* filename)
                : Data()
{
    this->name = new char[strlen(filename) + 1];
    strcpy(this->name, filename);

    FILE* file = fopen(filename, "rb");
    if (file != 0)
    {
        fseek(file, 0, SEEK_END);
        this->dataSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        this->data = new unsigned char[this->dataSize];
        size_t res = fread(this->data, this->dataSize, 1, file);

        fclose(file);
    }
    else throw "Cannot open file";
}

File::~File()
{
}
