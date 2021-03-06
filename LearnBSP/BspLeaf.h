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

#include "common/boundingbox.h"
#include "BspNode.h"
#include <set>

class BspFace;
class BspObject;

/*!
 * \brief
 */
class BspLeaf : public BspNode
{
public:
    BspLeaf();
    virtual ~BspLeaf();

    void renderLeafOnly();
    virtual void render();
    virtual void render(const float point[3]);
    void gatherVisibleObjectsLeafOnly(std::set<BspObject*>& objects);
    virtual void gatherVisibleObjects(std::set<BspObject*>& objects, const float point[3]);

    void addFace(BspFace* face);
    int getFaceCount() const;
    const std::set<BspFace*>& getFaces() const;

    virtual BspLeaf* getChild(const float point[3]);

    void addVisibleLeaf(BspLeaf* leaf);
    virtual void addObject(BspObject* object);

    void setBoundingBox(const BoundingBox& bb);
    const BoundingBox& getBoundingBox() const;

private:
    /*! \brief  */
    std::set<BspFace*> mFaces;
    /*! \brief  */
    std::set<BspLeaf*> mVisibleLeafs;
    /*! \brief  */
    std::set<BspObject*> mObjects;
    /*! \brief */
    BoundingBox mBB;

};

#endif	/* _BSPLEAF_H */

