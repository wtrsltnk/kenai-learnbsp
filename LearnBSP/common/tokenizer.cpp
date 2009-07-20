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

#include "tokenizer.h"
#include <string>

using namespace std;

/*
 * \brief
 */
class Tokenizer::PIMPL
{
public:
    /*
     * \brief
     * \param data
     * \param size
     */
    PIMPL(const unsigned char* data, int size) : mData(data), mDataSize(size), mCursor(0) {}
    /* \brief */
    const unsigned char* mData;
    /* \brief */
    int mDataSize;
    /* \brief */
    int mCursor;
    /* \brief */
    string mToken;
};

/*
 * \brief
 * \param data
 * \param size
 */
Tokenizer::Tokenizer(const unsigned char* data, int size)
        : pimpl(new Tokenizer::PIMPL(data, size))
{
    pimpl->mToken = "";
}

/*
 * \brief
 */
Tokenizer::~Tokenizer()
{
    delete pimpl;
}

/*
 * \brief
 * \param c
 * \return 
 */
bool isSpaceCharacter(const char c)
{
    return (c <= ' ');
}

/*
 * \brief
 * \return
 */
bool Tokenizer::nextToken()
{
    pimpl->mToken = "";

    while (pimpl->mCursor <= pimpl->mDataSize && isSpaceCharacter(pimpl->mData[pimpl->mCursor]))
		pimpl->mCursor++;

    if (pimpl->mData[pimpl->mCursor] == '\"')
    {
        pimpl->mCursor++;

        while (pimpl->mCursor <= pimpl->mDataSize && pimpl->mData[pimpl->mCursor] != '\"')
        {
            pimpl->mToken += pimpl->mData[pimpl->mCursor];
            pimpl->mCursor++;
        }

        pimpl->mCursor++;
    }
    else
    {
        while (pimpl->mCursor <= pimpl->mDataSize && !isSpaceCharacter(pimpl->mData[pimpl->mCursor]))
        {
            pimpl->mToken += pimpl->mData[pimpl->mCursor];
            pimpl->mCursor++;
        }
    }

    return (pimpl->mCursor < pimpl->mDataSize);
}

/*
 * \brief
 * \return
 */
const char* Tokenizer::getToken() const
{
    return pimpl->mToken.c_str();
}
