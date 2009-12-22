/*
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

#ifndef _Q3BSPWORLD_H
#define	_Q3BSPWORLD_H

#include "BspWorld.h"
#include "Q3BspData.h"

/*!
 * \brief
 */
class Q3BspWorld : public BspWorld
{
public:
    Q3BspWorld();
    virtual ~Q3BspWorld();

protected:
    virtual bool onOpen(const Data& data, TextureLoader& textureLoader);
    
private:
    bool parseFaces(Q3BspData& bsp);
    bool parseLightmaps(Q3BspData& bsp);
    bool parseTextures(Q3BspData& bsp);
    bool parseBrushes(Q3BspData& bsp);

};

#endif	/* _Q3BSPWORLD_H */

