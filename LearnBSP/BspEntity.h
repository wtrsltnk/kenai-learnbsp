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

#ifndef _BSPENTITY_H
#define	_BSPENTITY_H

#include "common/tokenizer.h"
#include <map>
#include <string>

/*!
 * \brief
 */
typedef std::map<std::string, std::string> Map;

/*!
 * \brief
 */
class BspEntity
{
public:
    BspEntity();
    virtual ~BspEntity();

    virtual const char* getClassName() const;
    virtual int getKeyCount() const;
    virtual const char* getKey(int index) const;
    virtual const char* getValue(int index) const;
    virtual const char* getValue(const char* key) const;
    const Map& getValues() const;

    bool parseFromTokenizer(Tokenizer& tok);
    
private:
    /*! \brief */
    Map mValues;

};

#endif	/* _BSPENTITY_H */

