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

/*!
 * \brief
 */
BspLeaf::BspLeaf()
    : mFaceCount(0), mFaces(NULL)
{
}

/*!
 * \brief
 */
BspLeaf::~BspLeaf()
{
    if (this->mFaces != NULL)
        delete []this->mFaces;
}

/*!
 * \brief Sets the number of faces and initializes the face array
 * \param count The new number of faces
 *
 * This resets the array to all NULL values
 */
void BspLeaf::setFaceCount(int count)
{
    if (count <= 0)
        return;

    if (this->mFaces != NULL)
        delete []this->mFaces;

    this->mFaceCount = count;
    this->mFaces= new BspFace*[count];
    for (int i = 0; i < count; i++)
        this->mFaces[i] = NULL;
}

/*!
 * \brief Set the face in the given index
 * \param face Pointer to the face to set
 * \param index The index in the array for this face
 */
void BspLeaf::setFace(BspFace* face, int index)
{
    if (index < 0 || index >= this->mFaceCount)
        return;

    this->mFaces[index] = face;
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
 * \brief
 * \param renderPvs
 */
void BspLeaf::render(bool renderPvs) const
{
    for (int f = 0; f < this->mFaceCount; f++)
    {
        if (this->mFaces[f] != NULL) this->mFaces[f]->render();
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
