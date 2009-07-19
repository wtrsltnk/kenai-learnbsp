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

#pragma pack(1)

/*!
 * \brief
 */
typedef struct sTGAHeader
{
    unsigned char idLength;
    unsigned char colormapType;
    unsigned char imageType;
    unsigned short colormapIndex;
    unsigned short colormapLength;
    unsigned char colormapSize;
    unsigned short xOrigin, yOrigin;
    unsigned short width, height;
    unsigned char pixelSize;
    unsigned char attributes;
    
} tTGAHeader;

#pragma pack()

/*!
 * \brief
 * \param texture
 * \param data
 * \return
 */
bool openTarga(Texture& texture, const Data& data)
{
    tTGAHeader* header = (tTGAHeader*)data.data;

    texture.bpp = header->pixelSize >> 3;
    texture.width = header->width;
    texture.height = header->height;
    int newDataSize = header->width * header->height * texture.bpp;
    texture.data = new unsigned char[newDataSize];
    memset(texture.data, 155, newDataSize);
    unsigned char* imageData = data.data + sizeof(tTGAHeader) + header->idLength;

    if (header->imageType != 9 && header->imageType != 10 && header->imageType != 11)
    {
        if (data.dataSize >= sizeof(tTGAHeader) + header->idLength + newDataSize)
            memcpy(texture.data, imageData, newDataSize);
        else
            return false;
    }
    else
    {
/*
        unsigned char* scanline = new unsigned char[header->width * bpp];
        int offset = 0;

        for (int i = 0; i < header->height; i++)
        {
            if (TGADecodeScanLine(scanline, header->width, bpp, imageData) < 0)
                return NULL;

            memcpy(&data[offset], scanline, header->width * bpp);
            offset += (header->width * bpp);
        }

        free(scanline);
*/
    }

    if (texture.bpp > 1)
    {
          for (unsigned int c = 0; c < newDataSize; c += texture.bpp)
          {
             unsigned char t = texture.data[c];
             texture.data[c] = texture.data[c+2];
             texture.data[c+2] = t;
          }
    }

    //if (header->attributes & 0x20)  // bottom up, need to swap scanlines
    {
        unsigned char *temp = new unsigned char[header->width * texture.bpp];

        for (int i = 0; i < header->height/2; i++)
        {
            memcpy(temp, texture.data + i*header->width*texture.bpp, header->width*texture.bpp);
            memcpy(texture.data + i*header->width*texture.bpp, texture.data + (header->height-i-1)*header->width*texture.bpp, header->width*texture.bpp);
            memcpy(texture.data + (header->height-i-1)*header->width*texture.bpp, temp, header->width*texture.bpp);
        }

        delete []temp;
    }
    return true;
}
