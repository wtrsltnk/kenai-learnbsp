#ifndef _STRINGFUNCTIONS_H
#define	_STRINGFUNCTIONS_H

class StringFunctions
{
public: virtual ~StringFunctions() {}

public:
    static const char* getFilename(const char* fullname);
    static const char* getExtention(const char* fullname);;

};

#endif	/* _STRINGFUNCTIONS_H */

