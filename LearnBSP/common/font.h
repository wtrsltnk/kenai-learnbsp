#ifndef _FONT_H
#define	_FONT_H

/*
 * \brief
 */
class Font
{
public:
    Font();
    virtual ~Font();

    void openFromFile(const char* file);

    void setup();
    void cleanup();

    void render(int x, int y, const char* string, ...);

private:
    /* \brief */
    int mViewport[4];
    /* \brief */
    int base;
    /* \brief */
    unsigned int id;

};

#endif	/* _FONT_H */

