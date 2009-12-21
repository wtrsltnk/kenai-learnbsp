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

#include "BspLeaf.h"
#include "BspFace.h"
#include "BspObject.h"
#include "Collision.h"
#include "common/renderoperations.h"
#include <iostream>

/*!
 * \brief
 */
BspLeaf::BspLeaf()
{
}

/*!
 * \brief
 */
BspLeaf::~BspLeaf()
{
}

/*!
 * \brief
 * \param renderPvs
 */
void BspLeaf::render(bool renderPvs) const
{
    for (std::set<BspFace*>::const_iterator face = this->mFaces.begin(); face != this->mFaces.end(); ++face)
    {
        (*face)->render();
    }

    if (renderPvs)
    {
        for (std::set<BspLeaf*>::const_iterator itr = this->mVisibleLeafs.begin(); itr != this->mVisibleLeafs.end(); ++itr)
        {
            const BspLeaf* leaf = *itr;
            leaf->render(false);
        }
    }
}

/*!
 * \brief
 * \param objects
 * \param pvs
 */
void BspLeaf::gatherVisibleObjects(std::set<BspObject*>& objects, bool pvs) const
{
    for (std::set<BspObject*>::const_iterator object = this->mObjects.begin(); object != this->mObjects.end(); ++object)
    {
        objects.insert(*object);
    }

    if (pvs)
    {
        for (std::set<BspLeaf*>::const_iterator itr = this->mVisibleLeafs.begin(); itr != this->mVisibleLeafs.end(); ++itr)
        {
            const BspLeaf* leaf = *itr;
            leaf->gatherVisibleObjects(objects, false);
        }
    }
}

/*!
 * \brief Set the face in the given index
 * \param face Pointer to the face to set
 */
void BspLeaf::addFace(BspFace* face)
{
    this->mFaces.insert(face);
}

/*!
 * \brief Get's the number of faces in this leaf
 * \return Returns the number of faces in this leaf
 */
int BspLeaf::getFaceCount() const
{
    return this->mFaces.size();
}

/*!
 * \brief Adds a leaf to the posible visible leaf set of this leaf
 * \param leaf A pointer to the leaf that is posible visible from this leaf
 */
void BspLeaf::addVisibleLeaf(BspLeaf* leaf)
{
    this->mVisibleLeafs.insert(leaf);
}
/*!
 * \ brief
 * \param object
 */
void BspLeaf::addObject(BspObject* object)
{
    this->mObjects.insert(object);
}

/*!
 * \brief
 * \param bb
 */
void BspLeaf::setBoundingBox(const BoundingBox& bb)
{
    this->mBB = bb;
}

/*!
 * \brief
 * \return
 */
const BoundingBox& BspLeaf::getBoundingBox() const
{
    return this->mBB;
}
