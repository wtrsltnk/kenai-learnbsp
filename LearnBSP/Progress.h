/* 
 * File:   Progress.h
 * Author: wouter
 *
 * Created on December 31, 2009, 10:11 AM
 */

#ifndef _PROGRESS_H
#define	_PROGRESS_H

class Progress
{
public:
    virtual ~Progress() { }

    virtual void onChange(int type, const char* msg) = 0;
};


#endif	/* _PROGRESS_H */

