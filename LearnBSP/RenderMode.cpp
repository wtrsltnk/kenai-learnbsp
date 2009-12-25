/* 
 * File:   RenderMode.cpp
 * Author: wouter
 * 
 * Created on December 25, 2009, 1:22 AM
 */

#include "RenderMode.h"
#include <GL/gl.h>

RenderMode::RenderMode()
{
	this->mOrigin[0] = this->mOrigin[1] = this->mOrigin[2] = 0;
	this->mFxAmount = 1.0f;
	this->mFxMode = 4;
	this->mFxColor[0] = this->mFxColor[1] = this->mFxColor[2] = 1.0f;
}

RenderMode::~RenderMode()
{
}

/*!
 * \brief
 */
void RenderMode::setupFx() const
{
	glTranslatef(this->mOrigin[0], this->mOrigin[1], this->mOrigin[2]);
	switch (this->mFxMode)
	{
		case 1:	// Color blending
		{
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_ALPHA_TEST);
			glDisable(GL_BLEND);
			glColor3f(this->mFxColor[0], this->mFxColor[1], this->mFxColor[2]);
			break;
		}
		case 3:	// Glow blending
		case 5:	// Additive blending
		{
			glEnable(GL_TEXTURE_2D);
			glDisable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glColor4f(1.0f, 1.0f, 1.0f, this->mFxAmount);
			break;
		}
		case 4:	// Solid blending
		{
			glEnable(GL_TEXTURE_2D);

			// Enable alpha testing to make sure transparent textures are drawn correct
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GEQUAL, 0.8f);

			// Default blending acoording to the alpha value of texture
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0f, 1.0f, 1.0f, this->mFxAmount);
			break;
		}
		case 2:	// Texture blending
		{
			glEnable(GL_TEXTURE_2D);
			glDisable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glColor4f(1.0f, 1.0f, 1.0f, this->mFxAmount);
			break;
		}
		case 0:	// Normal blending
		default:
		{
			glEnable(GL_TEXTURE_2D);
			glDisable(GL_ALPHA_TEST);
			glDisable(GL_BLEND);
			break;
		}
	}
}

