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

#ifndef _BSPNODE_H
#define	_BSPNODE_H

#include "common/math3d.h"
#include "common/boundingbox.h"
#include <vector>

class BspLeaf;
class BspObject;
class Collision;

/*!
 * \brief
 */
class BspNode
{
public:
    BspNode();
    BspNode(BspLeaf* leaf);
    virtual ~BspNode();

    void render() const;
    void render(const float position[3]) const;

    Collision getCollision(const Vector3& start, const Vector3& end);

    void setPlane(float normal[3], float distance);
    const Plane& getPlane() const;

    void setChildren(BspNode* front, BspNode* back);
    const BspNode* getFront() const;
    const BspNode* getBack() const;
    const BspNode* getParent() const;

    const BspNode* getChild(const float point[3]) const;
    const BspLeaf* getLeaf(const float point[3]) const;
    const BspLeaf* getLeaf() const;

    void setBoundingBox(const BoundingBox& bb);
    const BoundingBox& getBoundingBox() const;

    void addObject(BspObject* object, const BoundingBox& bb);

    int index;
private:
    /*! \brief */
    BspNode* mParent;
    /*! \brief */
    BspNode* mFront;
    /*! \brief */
    BspNode* mBack;
    /*! \brief */
    Plane mSplit;
    /*! \brief */
    BspLeaf* mLeaf;
    /*! \brief */
    BoundingBox mBB;
    /*! \brief */
    std::vector<BspObject*> mObjects;
    
};

#endif	/* _BSPNODE_H */

