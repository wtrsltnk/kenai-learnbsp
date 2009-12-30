/* 
 * File:   common.cpp
 * Author: wouter
 * 
 * Created on December 24, 2009, 12:40 PM
 */

#include "common.h"
#include "opengl.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>

void Common::print(const char* format, ...)
{
	char destination[1024];
	va_list ap;

	va_start(ap, format);
	printf(format, ap);
	va_end(ap);
}

const char* Common::getFilename(const char* fullname)
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

const char* Common::getExtention(const char* fullname)
{
    return strrchr(fullname, '.');
}

int Common::stringLength(const char* string)
{
	return strlen(string);
}

const char* Common::stringCopy(char* destination, const char* source, int size)
{
	if (size > 0)
		return strncpy(destination, source, size);
	
	return strcpy(destination, source);
}

int Common::stringCompare(const char* str1, const char* str2, int size, bool casesensitive)
{
	if (size == -1)
	{
		if (casesensitive)
		{
			return strcasecmp(str1, str2);
		}
		return strcmp(str1, str2);
	}
	else
	{
		if (casesensitive)
		{
			return strncasecmp(str1, str2, size);
		}
		return strncmp(str1, str2, size);
	}
}

const char* Common::stringSplit(const char* haystack, const char* needle)
{
	return strstr(haystack, needle);
}

const char* Common::stringCharSplit(const char* haystack, int needle, bool reverse)
{
	if (reverse)
		return strrchr(haystack, needle);

	return strchr(haystack, needle);
}

char* Common::stringFormat(char* destination, const char* format, ...)
{
	va_list ap;

	va_start(ap, format);
		vsprintf(destination, format, ap);
	va_end(ap);

	return destination;
}

int Common::stringScan(const char* source, const char* format, ...)
{
	va_list ap;

	va_start(ap, format);
		int result = sscanf(source, format, ap);
	va_end(ap);

	return result;
}

void Common::renderBoundingBox(const BoundingBox& bb)
{
    glPushAttrib(GL_ENABLE_BIT);
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_LINES);
    // bottom
    glVertex3f(bb.getMins()[0], bb.getMins()[1], bb.getMins()[2]);
    glVertex3f(bb.getMaxs()[0], bb.getMins()[1], bb.getMins()[2]);

    glVertex3f(bb.getMaxs()[0], bb.getMins()[1], bb.getMins()[2]);
    glVertex3f(bb.getMaxs()[0], bb.getMaxs()[1], bb.getMins()[2]);

    glVertex3f(bb.getMaxs()[0], bb.getMaxs()[1], bb.getMins()[2]);
    glVertex3f(bb.getMins()[0], bb.getMaxs()[1], bb.getMins()[2]);

    glVertex3f(bb.getMins()[0], bb.getMaxs()[1], bb.getMins()[2]);
    glVertex3f(bb.getMins()[0], bb.getMins()[1], bb.getMins()[2]);
    // top
    glVertex3f(bb.getMins()[0], bb.getMaxs()[1], bb.getMaxs()[2]);
    glVertex3f(bb.getMaxs()[0], bb.getMaxs()[1], bb.getMaxs()[2]);

    glVertex3f(bb.getMaxs()[0], bb.getMaxs()[1], bb.getMaxs()[2]);
    glVertex3f(bb.getMaxs()[0], bb.getMins()[1], bb.getMaxs()[2]);

    glVertex3f(bb.getMaxs()[0], bb.getMins()[1], bb.getMaxs()[2]);
    glVertex3f(bb.getMins()[0], bb.getMins()[1], bb.getMaxs()[2]);

    glVertex3f(bb.getMins()[0], bb.getMins()[1], bb.getMaxs()[2]);
    glVertex3f(bb.getMins()[0], bb.getMaxs()[1], bb.getMaxs()[2]);

    //sides
    glVertex3f(bb.getMins()[0], bb.getMaxs()[1], bb.getMins()[2]);
    glVertex3f(bb.getMins()[0], bb.getMaxs()[1], bb.getMaxs()[2]);

    glVertex3f(bb.getMaxs()[0], bb.getMaxs()[1], bb.getMins()[2]);
    glVertex3f(bb.getMaxs()[0], bb.getMaxs()[1], bb.getMaxs()[2]);

    glVertex3f(bb.getMaxs()[0], bb.getMins()[1], bb.getMins()[2]);
    glVertex3f(bb.getMaxs()[0], bb.getMins()[1], bb.getMaxs()[2]);

    glVertex3f(bb.getMins()[0], bb.getMins()[1], bb.getMins()[2]);
    glVertex3f(bb.getMins()[0], bb.getMins()[1], bb.getMaxs()[2]);
    glEnd();

    glPopAttrib();
}

void Common::renderGrid(float gridsize, float gridcount)
{
    // TODO: zoek uit welke attrib je moet pushen om te zorgen dat de kleur gepushes wordt
    glPushAttrib(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    float x = (gridcount * gridsize) / 2;
    float y = (gridcount * gridsize) / 2;
    for (int i = 0; i <= gridcount; i++)
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(x, -(gridcount * gridsize) / 2, 0);
        glVertex3f(x,  (gridcount * gridsize) / 2, 0);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-(gridcount * gridsize) / 2, y, 0);
        glVertex3f( (gridcount * gridsize) / 2, y, 0);

        x -= gridsize;
        y -= gridsize;
    }
    glEnd();
    glPopAttrib();
}

void Common::renderCrosshair(float size)
{
	GLint mViewport[4];
    glGetIntegerv(GL_VIEWPORT, mViewport);

    // Save the current perspective state
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(mViewport[0], mViewport[2], mViewport[1], mViewport[3], -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Save the current blending attributes
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_TEXTURE_BIT);
    glBlendFunc(GL_SRC_COLOR, GL_DST_ALPHA);
    glEnable(GL_BLEND);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);

	float midx = mViewport[2] / 2;
	float midy = mViewport[3] / 2;
	glBegin(GL_LINES);
	glColor4f(1, 0, 0, 0.5f);
	glVertex2f(midx, midy - (size / 2) - 1);
	glVertex2f(midx, midy + (size / 2));
	glVertex2f(midx - (size / 2) - 1, midy);
	glVertex2f(midx + (size / 2) , midy);
	glEnd();

    glPopAttrib();

    // Get back the current perspective state
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

float Common::getTickCount()
{
	return glfwGetTime();
}

void* Common::memoryCopy(void* dest, const void* src, int size)
{
	return memcpy(dest, src, size);
}

void* Common::memorySet(void* dest, int c, int size)
{
	return memset(dest, c, size);
}

bool Common::fileExists(const char* filename)
{
	struct stat stat_base;
	return (stat(filename, &stat_base) == 0);
}