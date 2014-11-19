/* 
 * File:   Drawable.h
 * Author: jacob
 *
 * Created on November 19, 2014, 12:21 PM
 */

#ifndef DRAWABLE_H
#define	DRAWABLE_H

/* Simply implement draw function. */
class Drawable {
public:
    Drawable();
    Drawable(const Drawable& orig);
    virtual ~Drawable();
    virtual void draw();
    void set_pos(float, float);
    float getX();
    float getZ();
protected:
    /* I suggest adding these definitions to the objects constructor. 
     * That way u do not need to call set_pos every time. */
    float worldX, worldZ;
    
};

#endif	/* DRAWABLE_H */

