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

#define BI_RGB   0L
#define BI_RLE4  2L
#define BI_RLE8  4L

/*!
 * \brief
 */
typedef struct sBMPFileHeader
{
    unsigned char type[2];
    unsigned long size;
    unsigned long reserved;
    unsigned long offset;
    
} tBMPFileHeader;

/*!
 * \brief
 */
typedef struct sBMPInfoHeader
{
    unsigned long size;
    unsigned long width;
    unsigned long height;
    unsigned short planes;
    unsigned short bpp;
    unsigned long compression;
    unsigned long sizeImage;
    unsigned long XPelsPerMeter;
    unsigned long YPelsPerMeter;
    unsigned long colorUsed;
    unsigned long colorImportant;
    
} tBMPInfoHeader;

/*!
 * \brief
 */
typedef struct sBMPRGBQuad
{
  char rgbBlue;
  char rgbGreen;
  char rgbRed;
  char rgbReserved;

} tBMPRGBQuad;

#pragma pack()

bool parseBMPData(unsigned char* data, int datasize, tBMPRGBQuad* palette, int palettesize, tBMPInfoHeader* info, fs::Texture& texture);

/*!
 * \brief
 * \param texture
 * \param data
 * \return
 */
bool openBitmap(fs::Texture& texture, const Data& data)
{
    tBMPFileHeader fileHeader;
    tBMPInfoHeader info;
    tBMPRGBQuad* palette = NULL;
    int paletteSize = 0;
    unsigned char* temp = NULL;
    int dataSize = 0;
    
    data.read(&fileHeader);

    if (fileHeader.type[0] != 'B' || fileHeader.type[1] != 'M')
        return false;
    
    data.read(&info, 1, sizeof(tBMPFileHeader));
    
    texture.name = new char[strlen(data.name) + 1];
    strcpy(texture.name, data.name);
    texture.width = info.width;
    texture.height = info.height;

    switch (info.bpp)
    {
        case 1: texture.bpp = 3; paletteSize = 2; break;
        case 4: texture.bpp = 3; paletteSize = 16; break;
        case 8: texture.bpp = 3; paletteSize = 256; break;
        case 24: texture.bpp = 3; break;
        case 32: texture.bpp = 4; break;
    }
    
    if (paletteSize > 0)
    {
        palette =new tBMPRGBQuad[paletteSize];
        data.read(palette, paletteSize, sizeof(tBMPFileHeader) + sizeof(tBMPInfoHeader));
    }

    if (info.compression == BI_RGB)
        dataSize = info.width * info.height * (info.bpp / 8);
    else
        dataSize = info.sizeImage;

    if (dataSize > 0)
    {
        temp = new unsigned char[dataSize];
        data.read(temp, dataSize, fileHeader.offset);
    }

    texture.data = new unsigned char[texture.width * texture.height * texture.bpp];

    parseBMPData(temp, dataSize, palette, paletteSize, &info, texture);
    
    delete []palette;
    delete []temp;
    
    return true;
}

/*!
 * \brief
 * \param data
 * \param datasize
 * \param palette
 * \param palettesize
 * \param info
 * \param texture
 * \return 
 */
bool parseBMPData(unsigned char* data, int datasize, tBMPRGBQuad* palette, int palettesize, tBMPInfoHeader* info, fs::Texture& texture)
{
    switch (info->compression)
    {
        case BI_RGB:
        {
            int imagePixel = 0;
            int dataPixel = 0;

            // For each row. BMP saves scanlines bottom to top, so we start at the bottom
            for (int i = info->height-1; i >= 0; i--)
            {
                for (int j = 0; j < info->width; j++)
                {
                    dataPixel = (i * info->width) + j;

                    switch (info->bpp)
                    {
                        case 8:
                        {
                            texture.data[imagePixel * texture.bpp] = palette[data[dataPixel]].rgbBlue;
                            texture.data[imagePixel * texture.bpp + 1] = palette[data[dataPixel]].rgbGreen;
                            texture.data[imagePixel * texture.bpp + 2] = palette[data[dataPixel]].rgbRed;
                            break;
                        }
                        case 24:
                        {
                            texture.data[(imagePixel * texture.bpp)] = data[(dataPixel * texture.bpp) + 2];
                            texture.data[(imagePixel * texture.bpp) + 1] = data[(dataPixel * texture.bpp) + 1];
                            texture.data[(imagePixel * texture.bpp) + 2] = data[(dataPixel * texture.bpp)];
                            break;
                        }
                        case 32:
                        {
                            texture.data[(imagePixel * texture.bpp)] = data[(dataPixel * texture.bpp) + 2];
                            texture.data[(imagePixel * texture.bpp) + 1] = data[(dataPixel * texture.bpp) + 1];
                            texture.data[(imagePixel * texture.bpp) + 2] = data[(dataPixel * texture.bpp) + 0];
                            texture.data[(imagePixel * texture.bpp) + 3] = data[(dataPixel * texture.bpp) + 3];
                            break;
                        }
                    }
                    imagePixel++;
                }
            }
            return true;
        }
        case BI_RLE8:
        {
            throw "Run-length encoding is not supported\n";
            /*
            int imagePixel = 0;
            int dataPixel = 0;

            for (int i = 0; i < datasize; i++)
            {
                if (data[i] == 0x00)
                {
                    i++;
                    if (data[i] == 0x00)
                    {
                        // End of line
                    }
                    else if (data[i] == 0x01)
                    {
                        // End of bitmap
                        break;
                    }
                    else if (data[i] == 0x02)
                    {
                        // Delta
                        unsigned char horz = data[++i];
                        unsigned char vert = data[++i];
                        imagePixel += (this->width * horz);
                        imagePixel += vert;
                    }
                    else if ((data[i] >= 0x03) && (data[i] < 0xFF))
                    {
                    }
                    i++;
                }
                else
                {
                    unsigned char count = data[i++];
                    unsigned char pixel = data[i];
                    for (int j = 0; j < count; j++)
                    {
                        this->pixels[imagePixel * this->bpp] = palette[pixel].blue;
                        this->pixels[imagePixel * this->bpp + 1] = palette[pixel].green;
                        this->pixels[imagePixel * this->bpp + 2] = palette[pixel].red;
                    }
                }
            }
            //*/
            break;
        }
        case BI_RLE4:
        {
            throw "Run-length encoding is not supported\n";
            break;
        }
    }
    return false;
}

             //*/