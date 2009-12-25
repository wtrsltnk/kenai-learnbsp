/* 
 * File:   BspProp.cpp
 * Author: wouter
 * 
 * Created on December 25, 2009, 11:42 AM
 */

#include "BspProp.h"
#include "BspMesh.h"
#include "common/common.h"
#include <string.h>
#include <GL/gl.h>

BspProp::BspProp(float origin[3], const char* mesh)
	: BspObject("prop", BSP_PROP)
{
	this->mOrigin[0] = origin[0];
	this->mOrigin[1] = origin[1];
	this->mOrigin[2] = origin[2];
	strcpy(this->mMeshName, mesh);
}

BspProp::~BspProp()
{
}

bool BspProp::isType(const char* type) const
{
	if (strcasecmp(type, "prop") == 0)
		return true;

	return false;
}

void BspProp::render(RenderOptions& options) const
{
	glPushMatrix();
	glTranslatef(this->mOrigin[0], this->mOrigin[1], this->mOrigin[2]);
	if (this->mMesh != NULL)
	{
		this->mMesh->render(options);
	}
	else
	{
		float size = 100.0f;
		glBegin(GL_LINES);
		glVertex3f(size, size, size);
		glVertex3f(-size, -size, -size);
		glVertex3f(size, size, -size);
		glVertex3f(-size, -size, size);
		glVertex3f(size, -size, -size);
		glVertex3f(-size, size, size);
		glVertex3f(-size, -size, -size);
		glVertex3f(size, size, size);
		glEnd();
	}
	glPopMatrix();
}

const BspMesh* BspProp::getMesh() const
{
}

void BspProp::onThink(ThinkArgs& args)
{
}

void BspProp::onTouch(TouchArgs& args)
{
}

void BspProp::preCache()
{
	// Load Mesh here from mMesh
}