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

#include "Illusionary.h"

/*!
 * \brief
 * \param contex
 * \param name
 */
Illusionary::Illusionary(BspPluginContext& context, const char* name)
    : ShadedObject(context, name, FUNC_ILLUSIONARY)
{
}

/*!
 * \brief
 * \param orig
 */
Illusionary::Illusionary(const Illusionary& orig)
    : ShadedObject(orig.mContext, orig.getName(), FUNC_ILLUSIONARY), mMesh(NULL)
{
}

/*!
 * \brief
 */
Illusionary::~Illusionary()
{
}

/*!
 * \brief
 * \param time
 */
void Illusionary::render(double time)
{
    this->setupShader();
    if (this->mMesh != NULL)
    {
        this->mMesh->render();
    }
}

/*!
 * \brief
 * \param entityKeys
 * \return
 */
BspObject* Illusionary::createInstance(const std::map<std::string, std::string>& entityKeys, BspPluginContext& context)
{
    Illusionary* illusionary = new Illusionary(*this);

    illusionary->setShading(entityKeys);
    std::string strModel = entityKeys.at(std::string("model"));
    int model;
    sscanf(strModel.c_str(), "*%d", &model);
    illusionary->mMesh = context.getModel(model);

    if (entityKeys.find(std::string("origin")) != entityKeys.end())
    {
        std::string origin = entityKeys.at(std::string("origin"));
        sscanf(origin.c_str(), "%f %f %f", &illusionary->mOrigin[0], &illusionary->mOrigin[1], &illusionary->mOrigin[2]);
    }
    return illusionary;
}

/*!
 * \brief
 * \return
 */
const BspMesh* Illusionary::getMesh() const
{
    return this->mMesh;
}
