/* 
 * File:   BspProp.cpp
 * Author: wouter
 * 
 * Created on December 25, 2009, 11:42 AM
 */

#include "BspProp.h"
#include "common/common.h"
#include "BspEntity.h"
#include <GL/gl.h>
#include <iostream>

BspProp::BspProp(BspEntity* entity)
	: BspObject("prop", BSP_PROP), mMdlMesh(NULL), mEntity(entity)
{
	RenderMode::fromEntity(entity, this->mRenderMode);
}

BspProp::~BspProp()
{
	if (this->mMdlMesh != NULL)
		delete this->mMdlMesh;
}

bool BspProp::isType(const char* type) const
{
	if (Common::stringCompare(type, "prop") == 0)
		return true;

	return false;
}

void BspProp::render(RenderOptions& options)
{
	glPushMatrix();
	this->mRenderMode.setupFx();
	if (this->mMdlMesh != NULL)
		this->mMdlMesh->render();
	glPopMatrix();
}

void BspProp::onThink(ThinkArgs& args)
{
}

void BspProp::onTouch(TouchArgs& args)
{
}

void BspProp::preCache(fs::FileSystem& filesystem)
{
	const char* meshname = this->mEntity->getValue("model");
	std::cout << meshname << std::endl;
	this->mMdlMesh = (Mdl*)filesystem.openResource(Common::getFilename(meshname));

	if (this->mMdlMesh != NULL)
	{
		this->mMdlMesh->initialize();
	}
}