/* 
 * File:   RenderOptions.cpp
 * Author: wouter
 * 
 * Created on December 23, 2009, 5:36 PM
 */

#include "RenderOptions.h"

RenderOptions::RenderOptions(Camera* camera, double time)
	: mCamera(camera), mTime(time)
{
}

RenderOptions::~RenderOptions()
{
}

Camera* RenderOptions::getCamera()
{
	return this->mCamera;
}

double RenderOptions::getTime()
{
	return this->mTime;
}

