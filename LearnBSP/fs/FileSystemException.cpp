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

#include "FileSystemException.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/*!
 * \brief
 * \param message
 */
FileSystemException::FileSystemException(const char* message)
{
    this->mMessage = new char[strlen(message) + 1];
    strcpy(this->mMessage, message);
}

/*!
 * \brief
 * \param message
 */
FileSystemException::FileSystemException(const char* message, ...)
{
    char final[1024] = { 0 };
    va_list argp;

    va_start(argp, message);
    vsprintf(final, message, argp);
    va_end(argp);

    this->mMessage = new char[strlen(final) + 1];
    strcpy(this->mMessage, final);
}

/*!
 * \brief
 */
FileSystemException::~FileSystemException()
{
    delete []this->mMessage;
}

/*!
 * \brief
 * /return
 */
const char* FileSystemException::getMessage() const
{
    return this->mMessage;
}

