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

#ifndef _BSPFACE_H
#define	_BSPFACE_H

#include "common/plane.h"
#include "common/texture.h"
#include "common/opengl.h"
#include "hltypes.h"
/*!
 * \brief
 */
class BspFace
{
public:
    BspFace();
    virtual ~BspFace();

    void render();
    
    void setPlane(float normal[3], float distance);
    const Plane& getPlane() const;

    void setVertices(int first, int count);
    int getFirstVertex() const;
    int getVertexCount() const;

    void setFlags(int flags);

    void setTexture(Texture* texture);
    const Texture* getTexture() const;

    const Texture* setLightmap(const hl::tBSPFace& bspFace, float min[2], float max[2], const unsigned char* lightData, float brightness = 0.5f);

    int side;
private:
    /*! \brief */
    Plane mPlane;
    /*! \brief */
    int mFirstVertex;
    /*! \brief */
    int mVertexCount;
    /*! \brief */
    GLuint mFaceType;
    /*! \brief */
    int mFaceFlags;
    /*! \brief */
    Texture* mTexture;
    /*! \brief */
    Texture* mLightmap;

};

#endif	/* _BSPFACE_H */

