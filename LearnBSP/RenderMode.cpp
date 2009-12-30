/* 
 * File:   RenderMode.cpp
 * Author: wouter
 * 
 * Created on December 25, 2009, 1:22 AM
 */

#include "RenderMode.h"
#include "BspEntity.h"
#include <GL/gl.h>
#include <stdio.h>

RenderMode::RenderMode()
{
	this->mOrigin[0] = this->mOrigin[1] = this->mOrigin[2] = 0;
	this->mAngles[0] = this->mAngles[1] = this->mAngles[2] = 0;
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
    glRotatef (this->mAngles[1],  0, 0, 1);
    glRotatef (this->mAngles[0],  0, 1, 0);
    glRotatef (this->mAngles[2],  1, 0, 0);
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

void RenderMode::fromEntity(BspEntity* entity, RenderMode& rendermode)
{
	if (entity != NULL)
	{
		const Map& values = entity->getValues();
		for (Map::const_iterator value = values.begin(); value != values.end(); ++value)
		{
			if ((*value).first == "origin")
			{
				float x, y, z;
				if (sscanf((*value).second.c_str(), "%f %f %f", &x, &y, &z) != false)
				{
					rendermode.mOrigin[0] = x;
					rendermode.mOrigin[1] = y;
					rendermode.mOrigin[2] = z;
				}
			}
			else if ((*value).first == "angles")
			{
				float x, y, z;
				if (sscanf((*value).second.c_str(), "%f %f %f", &x, &y, &z) != false)
				{
					rendermode.mAngles[0] = x;
					rendermode.mAngles[1] = y;
					rendermode.mAngles[2] = z;
				}
			}
			else if ((*value).first == "rendermode")
			{
				int mode = 0;
				if (sscanf((*value).second.c_str(), "%d", &mode) != false)
					rendermode.mFxMode = mode;
			}
			else if ((*value).first == "rendercolor")
			{
				float r, g, b;
				if (sscanf((*value).second.c_str(), "%f %f %f", &r, &g, &b) != false)
				{
					rendermode.mFxColor[0] = (float)r / 255.0f;
					rendermode.mFxColor[1] = (float)g / 255.0f;
					rendermode.mFxColor[2] = (float)b / 255.0f;
				}
			}
			else if ((*value).first == "renderamt")
			{
				int renderamt;
				if (sscanf((*value).second.c_str(), "%d", &renderamt) != false)
					rendermode.mFxAmount = (float)renderamt / 255.0f;
			}
		}
	}
}