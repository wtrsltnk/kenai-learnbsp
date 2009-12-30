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
 */
void  BspLeaf::renderLeafOnly()
{
	RenderOptions options(NULL, 0);
    for (std::set<BspFace*>::iterator face = this->mFaces.begin(); face != this->mFaces.end(); ++face)
    {
        (*face)->render();
    }

	for (std::set<BspObject*>::iterator itr = this->mObjects.begin(); itr != this->mObjects.end(); ++itr)
	{
		BspObject* object = *itr;
		object->render(options);
	}
}

/*!
 * \brief
 * \param point
 */
void BspLeaf::render(const float point[3])
{
    for (std::set<BspFace*>::iterator face = this->mFaces.begin(); face != this->mFaces.end(); ++face)
    {
        (*face)->render();
    }

	for (std::set<BspLeaf*>::iterator itr = this->mVisibleLeafs.begin(); itr != this->mVisibleLeafs.end(); ++itr)
	{
		BspLeaf* leaf = *itr;
		leaf->renderLeafOnly();
	}
}

/*!
 * \brief
 * \param renderPvs
 */
void BspLeaf::render()
{
    for (std::set<BspFace*>::iterator face = this->mFaces.begin(); face != this->mFaces.end(); ++face)
    {
        (*face)->render();
    }

	for (std::set<BspLeaf*>::iterator itr = this->mVisibleLeafs.begin(); itr != this->mVisibleLeafs.end(); ++itr)
	{
		BspLeaf* leaf = *itr;
		leaf->renderLeafOnly();
	}
}

/*!
 * \brief
 * \param objects
 */
void BspLeaf::gatherVisibleObjectsLeafOnly(std::set<BspObject*>& objects)
{
    for (std::set<BspObject*>::iterator object = this->mObjects.begin(); object != this->mObjects.end(); ++object)
    {
        objects.insert(*object);
    }
}

/*!
 * \brief
 * \param objects
 * \param point
 */
void BspLeaf::gatherVisibleObjects(std::set<BspObject*>& objects, const float point[3])
{
    for (std::set<BspObject*>::iterator object = this->mObjects.begin(); object != this->mObjects.end(); ++object)
    {
        objects.insert(*object);
    }

	for (std::set<BspLeaf*>::iterator itr = this->mVisibleLeafs.begin(); itr != this->mVisibleLeafs.end(); ++itr)
	{
		BspLeaf* leaf = *itr;
		leaf->gatherVisibleObjectsLeafOnly(objects);
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
 * \brief Get's a reference to the set with faces
 * \return A reference to the set with face
 */
const std::set<BspFace*>& BspLeaf::getFaces() const
{
    return this->mFaces;
}

/*!
 * \brief gets the
 */
BspLeaf* BspLeaf::getChild(const float point[3])
{
	if (this->mBB.contains(point))
	{
		return this;
	}
	return NULL;
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
