#ifndef _FILESYSTEMEXCEPTION_H
#define	_FILESYSTEMEXCEPTION_H

/*!
 * \brief
 */
class FileSystemException
{
public:
    FileSystemException(const char* message);
    FileSystemException(const char* message, ...);
    virtual ~FileSystemException();

    const char* getMessage() const;
    
private:
    /*! \brief */
    char* mMessage;

};

#endif	/* _FILESYSTEMEXCEPTION_H */

