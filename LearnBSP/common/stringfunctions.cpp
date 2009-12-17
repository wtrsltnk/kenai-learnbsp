#include "stringfunctions.h"
#include <string.h>

const char* StringFunctions::getFilename(const char* fullname)
{
    if (fullname == NULL)
        return NULL;
    
    const char* slash = strrchr(fullname, '\\');
    const char* backslash = strrchr(fullname, '/');

    if (slash != NULL && backslash != NULL)
    {
        if (slash > backslash)
            return slash + 1;
        return backslash + 1;
    }

    if (slash != NULL)
        return slash + 1;

    if (backslash != NULL)
        return backslash + 1;

    return NULL;
}

const char* StringFunctions::getExtention(const char* fullname)
{
    return strrchr(fullname, '.');
}

