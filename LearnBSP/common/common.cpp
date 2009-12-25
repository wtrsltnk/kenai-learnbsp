/* 
 * File:   common.cpp
 * Author: wouter
 * 
 * Created on December 24, 2009, 12:40 PM
 */

#include "common.h"
#include "opengl.h"
#include <string.h>

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

void Common::renderBoundingBox(const BoundingBox& bb)
{
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
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

