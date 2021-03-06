#ifndef _TEXTURE_H
#define	_TEXTURE_H

#include "../Resource.h"

namespace fs
{

/*!
 * \brief
 */
class Texture : public Resource
{
public:
    Texture();
    Texture(const char* filename);
    virtual ~Texture();

    unsigned int upload();
    void unload();
    
    Texture* copy() const;
    void copyFrom(const Texture& from);

    void setName(const char* name);
    void setDimentions(int width, int height, int bpp = 3);

public:
    /*! \brief */
    char* name;
    /*! \brief */
    int width;
    /*! \brief */
    int height;
    /*! \brief */
    int bpp;
    /*! \brief */
    bool repeat;
    /*! \brief */
    unsigned char* data;
    /*! \brief */
    unsigned int glIndex;

};

}

#endif	/* _TEXTURE_H */

