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

#ifndef _DATA_H
#define	_DATA_H

/*!
 * \brief 
 */
class Data
{
public:
    Data();
    Data(const char* name, bool readFromFile = false);
    virtual ~Data();

    /*!
     * \brief
     * \param array
     * \param count
     * \param offset
     * \return 
     */
    template<typename T>
    bool read(T* array, int count = 1, long offset = 0) const
    {
        // Check if the file is big enough to contain the data you want to read
        if ((sizeof(T) * count) + offset > dataSize)
            return false;

        // Cast the data to the new Type and jump to the right offset
        T* tmp = (T*)(data + offset);

        // Copy all the elements you need from the
        for (int i = 0; i < count; i++)
            array[i] = tmp[i];

        return true;
    }

    Data* clone() const;
    void copyFrom(const Data& from);

public:
    /*! \brief */
    char* name;
    /*! \brief */
    long dataSize;
    /*! \brief */
    unsigned char* data;

};

#endif	/* _DATA_H */

