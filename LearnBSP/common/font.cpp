#include "font.h"
#include <GL/gl.h>
#include <GL/glfw.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/*
 * \brief
 */
Font::Font()
{
}

/*
 * \brief
 */
Font::~Font()
{
}

/*
 * \brief
 * \param file
 */
void Font::openFromFile(const char* file)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glfwLoadTexture2D(file, GLFW_BUILD_MIPMAPS_BIT);
}

/*
 * \brief
 */
void Font::setup()
{
    glGetIntegerv(GL_VIEWPORT, this->mViewport);
    
    GLfloat cx, cy;
    base=glGenLists(256);
    glBindTexture(GL_TEXTURE_2D, id);
    for (int loop = 0; loop < 256; loop++)
    {
        cx = float(loop%16) / 16.0f;
        cy = float(loop/16) / 16.0f;

        glNewList(base+loop,GL_COMPILE);
            glBegin(GL_QUADS);
                glTexCoord2f(cx, 1-cy-0.0625f); glVertex2i(0, 0);
                glTexCoord2f(cx+0.0625f, 1-cy-0.0625f); glVertex2i(16, 0);
                glTexCoord2f(cx+0.0625f, 1-cy); glVertex2i(16, 16);
                glTexCoord2f(cx, 1-cy); glVertex2i(0, 16);
            glEnd();
            glTranslated(12, 0, 0);
        glEndList();
    }
}

/*
 * \brief
 */
void Font::cleanup()
{
    glDeleteLists(base, 256);
}

/*
 * \brief
 * \param x
 * \param y
 * \param string
 * \param ...
 */
void Font::render(int x, int y, const char* string, ...)
{
    float size = 0.5f;
    char final[1024] = { 0 };
    va_list argp;

    va_start(argp, string);
    vsprintf(final, string, argp);
    va_end(argp);

    // Save the current perspective state
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(this->mViewport[0], this->mViewport[2], this->mViewport[1], this->mViewport[3], -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Save the current blending attributes
    glPushAttrib(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_COLOR, GL_DST_ALPHA);
    glEnable(GL_BLEND);

    // Select the right texture for the font (no lightmap)
    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

    glTranslated(x, y, 0);
    glListBase(base-32 + (128*0));
    glCallLists(strlen(final), GL_UNSIGNED_BYTE, final);

    glPopAttrib();

    // Get back the current perspective state
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
