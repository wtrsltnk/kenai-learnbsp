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

#include "data.h"
#include <string.h>
#include <stdio.h>

/*!
 * \brief
 */
Data::Data() : name(0), data(0), dataSize(0)
{
}

/*!
 * \brief 
 * \param name
 */
Data::Data(const char* name, bool readFromFile) : name(0), data(0), dataSize(0)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    if (readFromFile)
    {
        FILE* file = fopen(name, "rb");
        if (file != NULL)
        {
            fseek(file, 0, SEEK_END);
            this->dataSize = ftell(file);
            fseek(file, 0, SEEK_SET);
            if (this->dataSize > 0)
            {
                this->data = new unsigned char[this->dataSize];
                fread(this->data, 1, this->dataSize, file);
            }
            fclose(file);
        }
    }
}

/*!
 * \brief
 */
Data::~Data()
{
//    if (name != 0) delete []name;
    if (data != 0) delete []data;
}

/*!
 * \brief
 * \return
 */
Data* Data::clone() const
{
    Data* result = new Data(this->name);

    result->dataSize = dataSize;
    result->data = new unsigned char[dataSize];
    memcpy(result->data, data, dataSize);

    return result;
}

/*!
 * \brief
 * \param from
 */
void Data::copyFrom(const Data& from)
{
    if (this->data != NULL)
    {
        delete []this->data;
        this->data = NULL;
    }

    if (this->name != NULL)
    {
        delete []this->name;
        this->name = NULL;
    }

    this->name = new char[strlen(from.name) + 1];
    strcpy(this->name, from.name);

    this->dataSize = from.dataSize;
    this->data = new unsigned char[this->dataSize];
    memcpy(this->data, from.data, dataSize);
}

/*!
 * \brief
 * \return
 */
FILE* Data::getAsFile() const
{
    FILE* file = tmpfile();

    fwrite(this->data, this->dataSize, 1, file);
	fseek(file, 0, SEEK_SET);

    return file;
}
