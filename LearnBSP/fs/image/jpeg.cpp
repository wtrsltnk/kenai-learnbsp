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

#include "image.h"
#include <stdio.h>
#include <iostream>
extern "C" {
  #include <jpeglib.h>
}

bool openJpeg(Texture& texture, const DataBlock& data)
{
    struct jpeg_decompress_struct cinfo;

    FILE * file = data.getAsFile();

    if(file == NULL)
    {
        std::cout << "Could not open file" << std::endl;
        return false;
    }

    //Create an error handler
    jpeg_error_mgr jerr;

    //point the compression object to the error handler
    cinfo.err = jpeg_std_error(&jerr);

    //Initialize the decompression object
    jpeg_create_decompress(&cinfo);

    //Specify the data source
    jpeg_stdio_src(&cinfo, file);



    //Decode the jpeg data into the image
    //Read in the header
    jpeg_read_header(&cinfo, true);

    //start to decompress the data
    jpeg_start_decompress(&cinfo);

    //get the number of color channels
    int channels = cinfo.num_components;

    //Fill in class variables
    texture.bpp = channels;
    texture.width = cinfo.image_width;
    texture.height = cinfo.image_height;

    //Allocate memory for image
    texture.data = new unsigned char[texture.width * texture.height * channels];
    if(!texture.data)
    {
        std::cout << "Unable to allocate memory for temporary texture data" << std::endl;
        return false;
    }

    //Create an array of row pointers
    unsigned char ** rowPtr = new unsigned char * [texture.height];
    if(!rowPtr)
    {
        std::cout << ("Unable to allocate memory for row pointers") << std::endl;
        return false;
    }

    for(unsigned int i = 0; i < texture.height; ++i)
        rowPtr[i] = &(texture.data[i * texture.width * channels]);

    //Extract the pixel data
    int rowsRead = 0;
    while(cinfo.output_scanline < cinfo.output_height)
    {
        //read in this row
        rowsRead+=jpeg_read_scanlines(&cinfo, &rowPtr[rowsRead], cinfo.output_height - rowsRead);
    }

    //release memory used by jpeg
    jpeg_destroy_decompress(&cinfo);

    fclose(file);

    //delete row pointers
    if(rowPtr)
        delete []rowPtr;
    rowPtr = NULL;
    
    return true;
}
