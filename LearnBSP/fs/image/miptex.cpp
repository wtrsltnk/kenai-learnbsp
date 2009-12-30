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

#include "image.h"
#include <string.h>

/*!
 * \brief
 */
typedef struct sBSPMipTexHeader
{
    char name[16];
    unsigned int width;
    unsigned int height;
    unsigned int offsets[4];

} tBSPMipTexHeader;

/*!
 * \brief
 * \param texture
 * \param data
 * \return 
 */
bool openMiptex(fs::Texture& texture, const Data& data)
{
    tBSPMipTexHeader miptex;
    data.read(&miptex);

    int s = miptex.width * miptex.height;
    int bpp = 4;
    int paletteOffset = miptex.offsets[0] + s + (s/4) + (s/16) + (s/64) + 2;

    unsigned char* source = data.data + miptex.offsets[0];
    unsigned char* palette = data.data + paletteOffset;
    texture.data = new unsigned char[s * bpp];
    texture.width = miptex.width;
    texture.height = miptex.height;
    texture.bpp = 4;
    texture.name = new char[strlen(data.name) + 1];
    strcpy(texture.name, data.name);

    int j = 0;
    for (int i = 0; i < s; i++)
    {
        unsigned char r, g, b, a;
        r = palette[source[i]*3];
        g = palette[source[i]*3+1];
        b = palette[source[i]*3+2];
        a = 255;

        if (palette[source[i]*3] <= 5 && palette[source[i]*3+1] <= 5 &&palette[source[i]*3+2] == 255)
            r = g = b = a = 0;

        texture.data[j++] = r;
        texture.data[j++] = g;
        texture.data[j++] = b;
        texture.data[j++] = a;
    }
    
    return true;
}
