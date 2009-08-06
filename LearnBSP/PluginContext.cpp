/*
 * Learn BSP is a sample source code to see how a Half-Life level file
 * can be used in your 3D application
 * Copyright (C) 2009  Wouter Saaltink

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "PluginContext.h"
#include <stdlib.h>

/*!
 * \brief
 */
PluginContext::PluginContext()
    : mModelCount(0), mModels(NULL)
{
}

/*!
 * \brief
 */
PluginContext::~PluginContext()
{
}

/*!
 * \brief
 * \param modelCount
 * \param models
 */
void PluginContext::setModels(int modelCount, BspModel* models)
{
    this->mModelCount = modelCount;
    this->mModels = models;
}

/*!
 * \brief
 * \param meshname
 * \return
 */
BspMesh* PluginContext::getMesh(const char* meshname)
{
    return NULL;
}

/*!
 * \brief
 * \param model
 * \return
 */
BspMesh* PluginContext::getModel(int model)
{
    if (model >= 0 && model < this->mModelCount)
    {
        return &this->mModels[model];
    }
    return NULL;
}

