#ifndef _DATA_H
#define	_DATA_H

/*
 * \brief 
 */
class Data
{
public:
    Data();
    Data(const char* name);
    virtual ~Data();

    /*
     * \brief
     * \param array
     * \param count
     * \param offset
     * \return 
     */
    template<typename T>
    bool read(T* array, int count = 1, long offset = 0) const
    {
        // Check if the file is big enough to contain the data you want to read
        if ((sizeof(T) * count) + offset > dataSize)
            return false;

        // Cast the data to the new Type and jump to the right offset
        T* tmp = (T*)(data + offset);

        // Copy all the elements you need from the
        for (int i = 0; i < count; i++)
            array[i] = tmp[i];

        return true;
    }

    Data* clone() const;
    void copyFrom(const Data& from);

public:
    /* \brief */
    char* name;
    /* \brief */
    long dataSize;
    /* \brief */
    unsigned char* data;

};

#endif	/* _DATA_H */

