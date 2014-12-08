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
#include "Map.h"

#define GHOST_MAX_SPELL_COUNT 1

class Ghost : public Entity{
public:
    Ghost(float, float);
    Ghost(const Ghost& orig);
    void move(float, float);
    void update();
    void draw();
    void update_pos();
    void fire_Lazer();
    void toggleGhostAttractionRadius();
    //void map_outbound(int);

    virtual ~Ghost();
private:
    bool isPlayerNear();
    unsigned long long readyToFire;
    Spell* lazer_ref;
    Map* curr_map;
    Entity* curr_player;
    bool isChasing;
    bool drawGhostAttractionRadius;
};

#endif	/* GHOST_H */