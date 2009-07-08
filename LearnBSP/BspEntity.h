#ifndef _BSPENTITY_H
#define	_BSPENTITY_H

#include "common/tokenizer.h"
#include <map>
#include <string>

typedef std::map<std::string, std::string> Map;

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

    bool parseFromTokenizer(Tokenizer& tok);
    
private:
    Map mValues;

};

#endif	/* _BSPENTITY_H */

