#include "stringfunctions.h"
#include <string.h>

char* StringFunctions::getFilename(char* fullname)
{
    char* slash = strrchr(fullname, '\\');
    char* backslash = strrchr(fullname, '/');

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
