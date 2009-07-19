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

