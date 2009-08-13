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

#include "WorldSpawn.h"

/*!
 * \brief
 * \param context
 * \param name
 */
WorldSpawn::WorldSpawn(BspPluginContext& context, const char* name)
    : BspObject(context, name, WORLDSPAWN)
{
}

/*!
 * \brief
 * \param orig
 */
WorldSpawn::WorldSpawn(const WorldSpawn& orig)
    : BspObject(orig.mContext, orig.getName(), WORLDSPAWN)
{
}

/*!
 * \brief
 */
WorldSpawn::~WorldSpawn()
{
}

/*!
 * \brief
 * \param time
 */
void WorldSpawn::render(double time)
{
}

/*!
 * \brief
 * \param entityKeys
 * \return
 */
BspObject* WorldSpawn::createInstance(const std::map<std::string, std::string>& entityKeys, BspPluginContext& context)
{
    WorldSpawn* worldspawn = new WorldSpawn(this->mContext, this->getName());

    worldspawn->mMesh = context.getModel(0);

    return worldspawn;
}

/*!
 * \brief
 * \return
 */
const BspMesh* WorldSpawn::getMesh() const
{
    return NULL;
}

