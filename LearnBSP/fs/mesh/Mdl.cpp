/* 
 * File:   Mdl.cpp
 * Author: wouter
 * 
 * Created on December 28, 2009, 3:17 PM
 */

#include "../../common/opengl.h"
#include "Mdl.h"

Mdl::Mdl(Data& file, fs::FileSystem& filesystem)
	: fs::Resource(fs::HlMdlResource, file.name), filesystem(filesystem)
{
	this->file.copyFrom(file);
}

Mdl::~Mdl()
{
}

void Mdl::initialize()
{
	glActiveTexture(GL_TEXTURE0);
	this->model.Init( this->file, this->filesystem );
	this->model.SetSequence( 0 );

	this->model.SetController( 0, 0.0 );
	this->model.SetController( 1, 0.0 );
	this->model.SetController( 2, 0.0 );
	this->model.SetController( 3, 0.0 );
	this->model.SetMouth( 0 );
	this->model.SetSkin( 1 );
}

void Mdl::render()
{
	glActiveTexture(GL_TEXTURE0);
	
	this->model.DrawModel();

	glColor3f(1, 1, 1);
}

