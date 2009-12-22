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

#include "Q3BspWorld.h"
#include <iostream>
#include <string.h>

/*!
 * \brief
 */
Q3BspWorld::Q3BspWorld()
{
}

/*!
 * \brief
 */
Q3BspWorld::~Q3BspWorld()
{
}

/*!
 * \brief
 * \param file
 * return
 */
bool Q3BspWorld::onOpen(const Data& file, TextureLoader& textureLoader)
{
    if (!Q3BspData::testBSP(file))
        return false;

    Q3BspData bsp(file);

//    this->mFaceCount = bsp.faceCount;
//    this->mTextureCount = bsp.textureCount;
//
//    this->mFaces = new BspFace[this->mFaceCount];
//    this->mVertices = new Q3::tBSPVertex[this->mVertexCount];
//    this->mLightmaps = new Texture[this->mLightmapCount];
//    this->mTextures = new Texture[this->mTextureCount];
//
//	// Copy the vertices directly
//    memcpy(this->mVertices, bsp.vertices, sizeof(Q3::tBSPVertex) * this->mVertexCount);
//
//    if (!parseLightmaps(bsp))
//        return false;
//
//    if (!parseTextures(bsp))
//        return false;
//
//    if (!parseFaces(bsp))
//        return false;
//
//    if (!parseBrushes(bsp, dynamics))
//        return false;
//
//	// Upload the vertices
//	glVertexPointer(3, GL_FLOAT, sizeof(Q3::tBSPVertex), &this->mVertices[0].position[0]);
//
//	// Upload the texture coordinates for the regular texture
//	glTexCoordPointer(2, GL_FLOAT, sizeof(Q3::tBSPVertex), &this->mVertices[0].texcoord[0][0]);
//
//	// Upload the texture coordinates for the lightmap texture
//	glClientActiveTextureARB(GL_TEXTURE1_ARB);
//	glTexCoordPointer(2, GL_FLOAT, sizeof(Q3::tBSPVertex), &this->mVertices[0].texcoord[1][0]);
//	glClientActiveTextureARB(GL_TEXTURE0_ARB);

    return false;
}

/*!
 * \brief
 * \param bsp
 * \return
 */
//bool Q3BspWorld::parseFaces(Q3BspData& bsp)
//{
//    for (int f = 0; f < bsp.faceCount; f++)
//    {
//        this->mFaces[f].mFaceType = bsp.faces[f].type;
//        if (bsp.faces[f].type == BspFace::POLYGON)
//        {
//            this->mFaces[f].mFirstVertex = bsp.faces[f].firstVertex;
//			this->mFaces[f].mVertexCount = bsp.faces[f].vertexCount;
//            this->mFaces[f].mLightmap = &this->mLightmaps[bsp.faces[f].lm_index];
//            this->mFaces[f].mTexture = &this->mTextures[bsp.faces[f].texture];
//        }
//    }
//    return true;
//}

/*!
 * \brief
 * \param bsp
 * \return
 */
//bool Q3BspWorld::parseLightmaps(Q3BspData& bsp)
//{
//    glClientActiveTexture(GL_TEXTURE1);
//    for (int l = 0; l < bsp.lightmapCount; l++)
//    {
//        int dataSize = 128 * 128 * 3;
//        this->mLightmaps[l].setDimentions(128, 128, 3);
//        memcpy(this->mLightmaps[l].data, bsp.lightmaps[l].map, dataSize);
//
//        this->mLightmaps[l].upload();
//    }
//    return true;
//}

/*!
 * \brief
 * \param bsp
 * \return
 */
//bool Q3BspWorld::parseTextures(Q3BspData& bsp)
//{
//    glClientActiveTexture(GL_TEXTURE0);
//    for (int t = 0; t < bsp.textureCount; t++)
//    {
//        const char* file = StringFunctions::getFilename(bsp.textures[t].name);
//        const char* findfile = this->mFileSystem->findFile(file);
//        if (findfile != NULL)
//        {
//			std::cout << "Loading texture " << findfile << std::endl;
//            if (this->mFileSystem->openTexture(this->mTextures[t], findfile))
//                this->mTextures[t].upload();
//            else
//                std::cout << "Could not load " << findfile << std::endl;
//        }
//        else
//            std::cout << "Could not find " << file << std::endl;
//    }
//    return true;
//}

/*!
 * \brief
 * \param bsp
 * \return
 */
//bool Q3BspWorld::parseBrushes(Q3BspData& bsp, Dynamics& dynamics)
//{
//    for (int l = 0; l < bsp.leafCount; l++)
//    {
//        Q3::tBSPLeaf& leaf = bsp.leafs[l];
//        for (int b = 0; b < bsp.leafs[l].leafBrushCount; b++)
//        {
//            int leafBrush = bsp.leafBrushes[leaf.firstLeafBrush + b].brush;
//            Q3::tBSPBrush& brush = bsp.brushes[leafBrush];
//
//            bool isValidBrush = false;
//            brush.texture = -1;
//
//            btAlignedObjectArray<btVector3> planeEquations;
//            for (int s = 0; s < brush.brushSideCount; s++)
//            {
//                Q3::tBSPBrushSide& side = bsp.brushSides[brush.firstBrushSide + s];
//                Q3::tBSPPlane& plane = bsp.planes[side.plane];
//                btVector3 planeEq;
//                planeEq.setValue(
//                        plane.normal[0],
//                        plane.normal[1],
//                        plane.normal[2]);
//                planeEq[3] = 1.0f * -plane.distance;
//
//                planeEquations.push_back(planeEq);
//                isValidBrush = true;
//            }
//
//            if (isValidBrush)
//            {
//                btAlignedObjectArray<btVector3>	vertices;
//                btGeometryUtil::getVerticesFromPlaneEquations(planeEquations, vertices);
//
//                dynamics.addConvexVerticesCollider(vertices);
//            }
//        }
//    }
//    return true;
//}
