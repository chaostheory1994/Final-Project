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
};

#endif	/* FROZENORB_H */

