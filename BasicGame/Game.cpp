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

#include "Game.h"

/*!
 * \brief
 * \param contex
 * \param name
 */
Game::Game(BspPluginContext& context, const char* name)
    : BspObject(context, name, GAME)
{
}

/*!
 * \brief
 * \param orig
 */
Game::Game(const Game& orig)
    : BspObject(orig.mContext, orig.getName(), GAME)
{
}

/*!
 * \brief
 */
Game::~Game()
{
}

/*!
 * \brief
 * \param time
 */
void Game::render(double time)
{
}

/*!
 * \brief
 * \param entityKeys
 * \return
 */
BspObject* Game::createInstance(const std::map<std::string, std::string>& entityKeys, BspPluginContext& context)
{
    Game* game = new Game(this->mContext, this->getName());

    return game;
}

/*!
 * \brief
 * \return
 */
const BspMesh* Game::getMesh() const
{
    return NULL;
}


