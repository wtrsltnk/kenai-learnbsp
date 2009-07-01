#ifndef _TEXTURE_H
#define	_TEXTURE_H

/*!
 * \brief
 */
class Texture
{
public:
    Texture();
    virtual ~Texture();

    unsigned int upload();
    void unload();
    
    Texture* copy() const;
    void copyFrom(const Texture& from);

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

#endif	/* _TEXTURE_H */

