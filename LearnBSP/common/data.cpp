#include "data.h"
#include <string.h>

/*!
 * \brief
 */
Data::Data() : name(0), data(0), dataSize(0)
{
}

/*!
 * \brief 
 * \param name
 */
Data::Data(const char* name) : name(0), data(0), dataSize(0)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

/*!
 * \brief
 */
Data::~Data()
{
    if (name != 0) delete []name;
    if (data != 0) delete []data;
}

/*!
 * \brief
 * \return
 */
Data* Data::clone() const
{
    Data* result = new Data(this->name);

    result->dataSize = dataSize;
    result->data = new unsigned char[dataSize];
    memcpy(result->data, data, dataSize);

    return result;
}

/*!
 * \brief
 * \param from
 */
void Data::copyFrom(const Data& from)
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

    this->name = new char[strlen(from.name) + 1];
    strcpy(this->name, from.name);

    this->dataSize = from.dataSize;
    this->data = new unsigned char[this->dataSize];
    memcpy(this->data, from.data, dataSize);
}
