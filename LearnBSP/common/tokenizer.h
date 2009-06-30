#ifndef _TOKENIZER_H
#define	_TOKENIZER_H

/*
 * \brief
 */
class Tokenizer
{
public:
    Tokenizer(const unsigned char* data, int size);
    virtual ~Tokenizer();

    bool nextToken();
    const char* getToken() const;
    
private:
    /*
     * \brief
     */
    class PIMPL;
    /* \brief */
    PIMPL* pimpl;

};

#endif	/* _TOKENIZER_H */

