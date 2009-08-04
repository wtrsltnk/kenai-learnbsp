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

#ifndef _BSPMODEL_H
#define	_BSPMODEL_H

#include "common/boundingbox.h"
#include <BspMesh.h>
#include <vector>

class BspFace;
class BspNode;
class BspLeaf;
class BspEntity;

/*!
 * \brief
 */
class BspModel : public BspMesh
{
public:
    BspModel();
    virtual ~BspModel();

    virtual bool collides(float start[3], float end[3]) const;
    virtual void update(double time);
    virtual void render() const;

    const BspLeaf* getLeaf(const float position[3]) const;

    void setHeadNode(BspNode* node);
    const BspNode* getHeadNode() const;

    void addFace(BspFace* face);

    void setOrigin(Vector3 origin);
    const Vector3& getOrigin() const;

    void setBoundingBox(const BoundingBox& bb);
    const BoundingBox& getBoundingBox() const;

private:
    /*! \brief */
    BspNode* mHeadNode;
    /*! \brief */
    std::vector<BspFace*> mFaces;
    /*! \brief */
    Vector3 mOrigin;
    /*! \brief */
    BoundingBox mBB;

};

#endif	/* _BSPMODEL_H */

