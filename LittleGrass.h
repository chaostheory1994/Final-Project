/* 
 * File:   LittleGrass.h
 * Author: jacob
 *
 * Created on November 19, 2014, 12:39 PM
 */

#ifndef LITTLEGRASS_H
#define	LITTLEGRASS_H
#include "Drawable.h"

class LittleGrass : public Drawable{
public:
    LittleGrass(float, float);
    LittleGrass(const LittleGrass& orig);
    void draw();
    virtual ~LittleGrass();
private:

};

#endif	/* LITTLEGRASS_H */

