#ifndef _CAMERA_H
#define	_CAMERA_H

/*!
 * \brief
 */
class Camera
{
public:
    Camera();
    virtual ~Camera();
    
    void Update();
    
    void SetPosition(float position[3]);
    const float* getPosition() const;

    void SetRotation(float rotation[3]);
    const float* getRotation() const;

    const float* getForwardVector() const;
    const float* getLeftVector() const;
    const float* getUpVector() const;

    void MoveGlobal(float forward, float left, float up);
    void MoveLocal(float forward, float left, float up);

private:
    /*! \brief */
    float rotationMatrix[16];
    /*! \brief */
    float position[3];
    /*! \brief */
    float rotation[3];
   
};

#endif	/* _CAMERA_H */

