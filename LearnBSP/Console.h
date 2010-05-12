/* 
 * File:   Console.h
 * Author: wouter
 *
 * Created on December 30, 2009, 3:25 PM
 */

#ifndef _CONSOLE_H
#define	_CONSOLE_H

#include "FreeTypeFont.h"

class Console
{
    class Line
    {
    public:
        Line(const char* line, Line* next);
        virtual ~Line();

        char* line;
        Line* next;
    };
    
public:
    Console(int w, int h);
    virtual ~Console();

    void render();

    void addLine(const char* line);
    
private:
    int mWidth, mHeight;
    FreeTypeFont mFont;
    Line* mFirstLine;
    GLFWmutex mMutex;

};

#endif	/* _CONSOLE_H */

