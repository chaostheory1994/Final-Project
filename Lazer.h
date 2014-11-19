//
//  Lazer.h
//  finalproject3
//
//  Created by Kyle  on 11/18/14.
//  Copyright (c) 2014 Kyle . All rights reserved.
//

#ifndef LAZER_H
#define LAZER_H

#include "Spell.h"
#include "Defines.h"

class Lazer : public Spell{
public:
    Lazer();
    Lazer(const Lazer& orig);
    Spell* cast(Spell_Details*, unsigned long long);
    void update();
    void draw();
    //void complete();
    virtual ~Lazer();
private:
    //float direction;
};

#endif	/* LAZER_H */

