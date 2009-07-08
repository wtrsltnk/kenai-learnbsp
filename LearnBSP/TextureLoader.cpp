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

#include "TextureLoader.h"
#include "types.h"

/*!
 * \brief
 */
TextureLoader::TextureLoader()
{
}

/*!
 * \brief
 */
TextureLoader::~TextureLoader()
{
}

/*!
 * \brief
 * \param wadstring
 */
void TextureLoader::setWadFiles(const char* wadstring)
{
}

/*!
 * \brief
 * \param texture
 * \param textureData
 * \return
 */
bool TextureLoader::loadTexture(Texture& texture, const unsigned char* textureData)
{
    tBSPMipTexHeader* miptex = (tBSPMipTexHeader*)textureData;
    
    texture.setName(miptex->name);
    texture.setDimentions(miptex->width, miptex->height, 4);

    if (miptex->offsets[0] != 0)
    {
        int s = miptex->width * miptex->height;
        int paletteOffset = miptex->offsets[0] + s + (s/4) + (s/16) + (s/64) + 2;

        const unsigned char* source = textureData + miptex->offsets[0];
        const unsigned char* palette = textureData + paletteOffset;

        int j = 0;
        for (int i = 0; i < s; i++)
        {
            char r, g, b, a;
            r = palette[source[i]*3];
            g = palette[source[i]*3+1];
            b = palette[source[i]*3+2];
            a = 255;

            if (palette[source[i]*3] <= 5 && palette[source[i]*3+1] <= 5 && palette[source[i]*3+2] == 255)
                r = g = b = a = 0;

            texture.data[j++] = r;
            texture.data[j++] = g;
            texture.data[j++] = b;
            texture.data[j++] = a;
        }
    }
    else
    {
    }
    return true;
}

