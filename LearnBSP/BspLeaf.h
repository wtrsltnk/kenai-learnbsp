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

#ifndef _BSPLEAF_H
#define	_BSPLEAF_H

#include "BspFace.h"
#include <set>

/*!
 * \brief
 */
class BspLeaf
{
public:
    BspLeaf();
    virtual ~BspLeaf();

    void setFaceCount(int count);
    void setFace(BspFace* face, int index);

    void addVisibleLeaf(BspLeaf* leaf);

    void render(bool renderPvs = true) const;

    int index;
private:
    /*! \brief  */
    int mFaceCount;
    /*! \brief  */
    BspFace** mFaces;
    /*! \brief  */
    std::set<BspLeaf*> mVisibleLeafs;

};

#endif	/* _BSPLEAF_H */

