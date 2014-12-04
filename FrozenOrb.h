/* 
 * File:   FrozenOrb.h
 * Author: jacob
 *
 * Created on November 10, 2014, 10:40 AM
 */

#ifndef FROZENORB_H
#define	FROZENORB_H
#include "Spell.h"
#include "Defines.h"
#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <stdlib.h>
#else
#include <GL/glut.h>
#endif

class FrozenOrb : public Spell{
public:
    FrozenOrb();
    FrozenOrb(const FrozenOrb& orig);
    Spell* cast(Spell_Details*, unsigned long long);
    void update();
    void draw();
    //void complete();
    virtual ~FrozenOrb();
private:
    float direction;
    GLUquadricObj* shape;
};

#endif	/* FROZENORB_H */

