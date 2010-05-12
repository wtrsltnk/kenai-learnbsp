/* 
 * File:   Console.cpp
 * Author: wouter
 * 
 * Created on December 30, 2009, 3:25 PM
 */

#include "Console.h"
#include "common/common.h"
#include "fs/File.h"
#include "common/thread.h"
#include <stdlib.h>
#include <iostream>

Console::Console(int w, int h)
	: mWidth(w), mHeight(h), mFirstLine(NULL)
{
//	Mutexer m(this->mMutex);
	
	fs::File font("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");
	if (this->mFont.initialize(font, 14.0f) == false)
		std::cout << "Initialize font failed" << std::endl;
}

Console::~Console()
{
//	Mutexer m(this->mMutex);

	Line* line = this->mFirstLine;
	while (line != NULL)
	{
		Line* tmp = line;
		line = line->next;
		delete tmp;
	}
}

void Console::addLine(const char* line)
{
//	Mutexer m(this->mMutex);
	
	this->mFirstLine = new Line(line, this->mFirstLine);
}

void Console::render()
{
//	Mutexer m(this->mMutex);

	glPushAttrib(GL_TEXTURE_BIT);
	glDisable(GL_CULL_FACE);
    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f(0, 0.4f, 0.8f, 0.8f);
	glBegin(GL_QUADS);
	glVertex3f(10, 10,-1);
	glVertex3f(this->mWidth - 10, 10,-1);
	glVertex3f(this->mWidth - 10, this->mHeight - 10,-1);
	glVertex3f(10, this->mHeight - 10,-1);
	glEnd();

	glColor4f(1, 1, 1, 1);
	float pos[3] = { 20, 20, 0 };
	Line* line = this->mFirstLine;
	while (line != NULL)
	{
		this->mFont.print(pos[0], pos[1], "%s", line->line);
		pos[1] += 20.0f;
		line = line->next;
	}
	
	glEnable(GL_CULL_FACE);
	glPopAttrib();
}

Console::Line::Line(const char* line, Console::Line* next)
	: next(next)
{
	this->line = new char[Common::stringLength(line) + 1];
	Common::stringCopy(this->line, line);
}

Console::Line::~Line()
{
	delete []this->line;
}

