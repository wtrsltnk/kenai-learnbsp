#include "BspEntity.h"
#include <string.h>

BspEntity::BspEntity()
{
}

BspEntity::~BspEntity()
{
}

const char* BspEntity::getClassName() const
{
    return getValue("classname");
}

int BspEntity::getKeyCount() const
{
    return int(this->mValues.size());
}

const char* BspEntity::getKey(int index) const
{
    if (index < 0 || index >= int(this->mValues.size()))
        return "";
    
    Map::const_iterator itr = this->mValues.begin();
    
    for (int i = 0; i < index; i++)
        ++itr;
    
    return itr->first.c_str();
}

const char* BspEntity::getValue(int index) const
{
    if (index < 0 || index >= int(this->mValues.size()))
        return "";

    Map::const_iterator itr = this->mValues.begin();

    for (int i = 0; i < index; i++)
        ++itr;

    return itr->second.c_str();
}

const char* BspEntity::getValue(const char* key) const
{
    Map::const_iterator itr = mValues.find(key);
    if (itr != mValues.end())
        return itr->second.c_str();
    return NULL;
}

bool BspEntity::parseFromTokenizer(Tokenizer& tok)
{
    while (tok.nextToken() && strcmp(tok.getToken(), "}") != 0)
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
