/* 
 * File:   FreeTypeFont.h
 * Author: wouter
 *
 * Created on October 24, 2009, 10:33 PM
 */

#ifndef _FREETYPEFONT_H
#define	_FREETYPEFONT_H

#include <GL/gl.h>

class FreeTypeFont
{
public:
    FreeTypeFont();
    virtual ~FreeTypeFont();

    bool initialize(const char* filename, int height);
    void destroy();

    void print(float x, float y, const char* fmt, ...);
    void print2(float position[3], float rotation[4], const char* fmt, ...);

private:
    float mHeight;
    GLuint* mTextures;
    GLuint mListBase;

};

#endif	/* _FREETYPEFONT_H */

