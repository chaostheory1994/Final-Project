/* 
 * File:   FOIcebolt.h
 * Author: jacob
 *
 * Created on November 10, 2014, 11:54 AM
 */

#ifndef FOICEBOLT_H
#define	FOICEBOLT_H
#include "Defines.h"
#include "Spell.h"

class FOIcebolt : public Spell{
public:
    FOIcebolt(float, float, float);
    FOIcebolt();
    FOIcebolt(const FOIcebolt& orig);
    Spell* cast(Spell_Details*, unsigned long long);
    void update();
    void draw();
    virtual ~FOIcebolt();
private:
    float direction;
};

#endif	/* FOICEBOLT_H */

