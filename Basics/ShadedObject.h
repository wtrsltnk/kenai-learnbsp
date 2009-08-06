/* 
 * File:   ShadedObject.h
 * Author: wouter
 *
 * Created on August 4, 2009, 5:14 PM
 */

#ifndef _SHADEDOBJECT_H
#define	_SHADEDOBJECT_H

#include <BspObject.h>
#include <map>
#include <string>

class ShadedObject : public BspObject
{
public:
    ShadedObject(BspPluginContext& context, const char* name, int type);
    virtual ~ShadedObject();

    void setShading(const std::map<std::string, std::string>& entityKeys);

    void setFxMode(int mode);
    int getFxMode() const;

    void setFxColor(float color[3]);
    const float* getFxColor() const;

    void setFxAmount(float amount);
    float getFxAmount() const;
    
protected:
    void setupShader() const;

    /*! \brief */
    int mFxMode;
    /*! \brief */
    float mFxColor[3];
    /*! \brief */
    float mFxAmount;

};

#endif	/* _SHADEDOBJECT_H */

