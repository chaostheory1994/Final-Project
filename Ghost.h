//
//  Ghost.h
//  finalproject3
//
//  Created by Kyle  on 11/10/14.
//  Copyright (c) 2014 Kyle . All rights reserved.
//

#ifndef GHOST_H
#define	GHOST_H
#include "Spell.h"
#include "Entity.h"

//#define MAX_SPELL_COUNT 0

class Ghost : public Entity{
public:
    Ghost(float, float);
    Ghost(const Ghost& orig);
    void move(float, float);
    void update();
    void draw(float);
    void update_pos();
    //void map_outbound(int);
    virtual ~Ghost();
private:
};

#endif	/* GHOST_H */