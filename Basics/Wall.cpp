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

#include "Wall.h"

/*!
 * \brief
 * \param name
 */
Wall::Wall(BspPluginContext& context, const char* name)
    : ShadedObject(context, name, FUNC_WALL)
{
}

/*!
 * \brief
 * \param orig
 */
Wall::Wall(const Wall& orig)
    : ShadedObject(orig.mContext, orig.getName(), FUNC_WALL), mMesh(NULL)
{
}

/*!
 * \brief
 */
Wall::~Wall()
{
}

/*!
 * \brief
 * \param time
 */
void Wall::render(double time)
{
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
BspObject* Wall::createInstance(const std::map<std::string, std::string>& entityKeys, BspPluginContext& context)
{
    Wall* wall = new Wall(*this);

    setShading(entityKeys);
    std::string strModel = entityKeys.at(std::string("model"));
    int model;
    sscanf(strModel.c_str(), "*%d", &model);
    wall->mMesh = context.getModel(model);

    if (entityKeys.find(std::string("origin")) != entityKeys.end())
    {
        std::string origin = entityKeys.at(std::string("origin"));
        sscanf(origin.c_str(), "%f %f %f", &this->mOrigin[0], &this->mOrigin[1], &this->mOrigin[2]);
    }
    return wall;
}

/*!
 * \brief
 * \return
 */
const BspMesh* Wall::getMesh() const
{
    return this->mMesh;
}

