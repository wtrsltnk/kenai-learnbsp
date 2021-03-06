#include "texture.h"
#include "../../common/opengl.h"
#include "../../common/common.h"

using namespace fs;

/*!
 * \brief
 */
Texture::Texture()
        : Resource(fs::TextureResource, ""), name(0), width(0), height(0), bpp(0), repeat(true), data(0), glIndex(0)
{
}

/*!
 * \brief
 */
Texture::Texture(const char* filename)
        : Resource(fs::TextureResource, filename), name(0), width(0), height(0), bpp(0), repeat(true), data(0), glIndex(0)
{
	this->setName(filename);
}

/*!
 * \brief
 */
Texture::~Texture()
{
    if (name != 0) delete []name;
    if (data != 0) delete []data;
}

/*!
 * \brief
 * \return 
 */
unsigned int Texture::upload()
{
	GLuint format = GL_RGB;

	switch (this->bpp)
	{
		case 3: format = GL_RGB; break;
		case 4: format = GL_RGBA; break;
	}

	glGenTextures(1, &this->glIndex);
	glBindTexture(GL_TEXTURE_2D, this->glIndex);

	if (this->repeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, this->data);

	return this->glIndex;
}

/*!
 * \brief
 */
void Texture::unload()
{
    glDeleteTextures(1, &this->glIndex);
}

/*!
 * \brief
 * \return 
 */
Texture* Texture::copy() const
{
    Texture* result = new Texture(this->name);

    result->width = this->width;
    result->height = this->height;
    result->bpp = this->bpp;
    result->repeat = this->repeat;
    result->glIndex = this->glIndex;
    int dataSize = result->width * result->height * result->bpp;
    if (dataSize > 0)
    {
        result->data = new unsigned char[dataSize];
        Common::memoryCopy(result->data, data, dataSize);
    }
    else
    {
        delete result;
        result = NULL;
    }

    return result;
}

/*!
 * \brief
 * \param from
 */
void Texture::copyFrom(const Texture& from)
{
    if (this->data != NULL)
    {
        delete []this->data;
        this->data = NULL;
    }

    if (this->name != NULL)
    {
        delete []this->name;
        this->name = NULL;
    }

    if (from.name != NULL)
    {
        this->name = new char[Common::stringLength(from.name) + 1];
        Common::stringCopy(this->name, from.name);
    }

    this->width = from.width;
    this->height = from.height;
    this->bpp = from.bpp;
    this->repeat = from.repeat;
    this->glIndex = from.glIndex;
    int dataSize = this->width * this->height * this->bpp;
    if (dataSize > 0)
    {
        this->data = new unsigned char[dataSize];
        Common::memoryCopy(this->data, from.data, dataSize);
    }
}

/*!
 * \brief
 * \param name
 */
void Texture::setName(const char* name)
{
    if (name != NULL)
    {
        if (this->name != NULL)
        {
            delete []this->name;
            this->name = NULL;
        }

        this->name = new char[Common::stringLength(name) + 1];
        Common::stringCopy(this->name, name);
    }
}

/*!
 * \brief
 * \param width
 * \param height
 */
void Texture::setDimentions(int width, int height, int bpp)
{
    if (this->glIndex != 0)
        return;
    
    if (this->data != NULL)
    {
        delete []this->data;
        this->data = NULL;
    }

    this->width = width;
    this->height = height;
    this->bpp = bpp;
    int dataSize = this->width * this->height * this->bpp;
    if (dataSize > 0)
    {
        this->data = new unsigned char[dataSize];
    }
}
