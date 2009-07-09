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

#include "BspNode.h"
#include "BspEntity.h"
#include "common/boundingbox.h"
#include <vector>

/*!
 * \brief
 */
class BspModel
{
public:
    BspModel();
    virtual ~BspModel();

    void render(bool renderHeadNode) const;

    const BspLeaf* getLeaf(const float position[3]) const;

    void setHeadNode(BspNode* node);
    const BspNode* getHeadNode() const;

    void setEntity(BspEntity* entity);
    const BspEntity* getEntity() const;

    void addFace(BspFace* face);

    void setOrigin(Vector3 origin);
    const Vector3& getOrigin() const;

    void setBoundingBox(const BoundingBox& bb);
    const BoundingBox& getBoundingBox() const;
    
private:
    /*! \brief */
    BspNode* mHeadNode;
    /*! \brief */
    BspEntity* mEntity;
    /*! \brief */
    std::vector<BspFace*> mFaces;
    /*! \brief */
    Vector3 mOrigin;
    /*! \brief */
    BoundingBox mBB;

};

#endif	/* _BSPMODEL_H */

