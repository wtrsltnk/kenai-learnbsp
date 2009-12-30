/* 
 * File:   common.h
 * Author: wouter
 *
 * Created on December 24, 2009, 12:40 PM
 */

#ifndef _COMMON_H
#define	_COMMON_H

#ifndef NULL
#define NULL 0
#endif

#include "boundingbox.h"

class Common
{
public:
    virtual ~Common() { }

    /// Print functions
    static void print(const char* format, ...);

    /// String functions
    static const char* getFilename(const char* fullname);
    static const char* getExtention(const char* fullname);
    static int stringLength(const char* string);
    static const char* stringCopy(char* destination, const char* source, int size = -1);
    static int stringCompare(const char* str1, const char* str2, int size = -1, bool casesensitive = false);
    static const char* stringSplit(const char* haystack, const char* needle);
    static const char* stringCharSplit(const char* haystack, int needle, bool reverse = false);
    static char* stringFormat(char* destination, const char* format, ...);
    static int stringScan(const char* source, const char* format, ...);

    /// Render functions
    static void renderBoundingBox(const BoundingBox& bb);
    static void renderGrid(float gridsize, float gridcount);
    static void renderCrosshair(float size);

    /// Time functions
    static float getTickCount();

    /// Memory copy
    static void* memoryCopy(void* dest, const void* src, int size);
    static void* memorySet(void* dest, int c, int size);

    /// File functions
    static bool fileExists(const char* filename);
};

#endif	/* _COMMON_H */

