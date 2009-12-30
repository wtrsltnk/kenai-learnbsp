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

#include "BspEntity.h"
#include "common/common.h"
#include <iostream>

/*!
 * \brief
 */
BspEntity::BspEntity()
{
}

/*!
 * \brief
 */
BspEntity::~BspEntity()
{
}

/*!
 * \brief
 * \return
 */
const char* BspEntity::getClassName() const
{
    return getValue("classname");
}

/*!
 * \brief
 * \return
 */
int BspEntity::getKeyCount() const
{
    return int(this->mValues.size());
}

/*!
 * \brief
 * \param index
 * \return 
 */
const char* BspEntity::getKey(int index) const
{
    if (index < 0 || index >= int(this->mValues.size()))
        return "";
    
    Map::const_iterator itr = this->mValues.begin();
    
    for (int i = 0; i < index; i++)
        ++itr;
    
    return itr->first.c_str();
}

/*!
 * \brief
 * \param index
 * \return
 */
const char* BspEntity::getValue(int index) const
{
    if (index < 0 || index >= int(this->mValues.size()))
        return "";

    Map::const_iterator itr = this->mValues.begin();

    for (int i = 0; i < index; i++)
        ++itr;

    return itr->second.c_str();
}

/*!
 * \brief
 * \param key
 * \return
 */
const char* BspEntity::getValue(const char* key) const
{
    Map::const_iterator itr = mValues.find(key);
    if (itr != mValues.end())
        return itr->second.c_str();
    return NULL;
}

/*!
 * \brief
 * \param tok
 * \return
 */
bool BspEntity::parseFromTokenizer(Tokenizer& tok)
{
    while (tok.nextToken() && Common::stringCompare(tok.getToken(), "}") != 0)
    {
        std::string key = tok.getToken();
        if (!tok.nextToken())
            break;

        std::string value = tok.getToken();
        if (value == "}")
            return false;
        
        this->mValues.insert(std::pair<std::string, std::string>(key, value));
    }
    return true;
}

/*!
 * \brief
 */
void BspEntity::print()
{
	for (Map::const_iterator itr = this->mValues.begin(); itr != this->mValues.end(); ++itr)
	{
		std::cout << (*itr).first << " : " << (*itr).second << std::endl;
	}
	std::cout << std::endl;
}

/*!
 * \brief
 * \return
 */
const Map& BspEntity::getValues() const
{
    return this->mValues;
}
