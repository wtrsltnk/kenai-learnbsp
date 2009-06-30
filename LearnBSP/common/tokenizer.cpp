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
