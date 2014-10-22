/* 
 * File:   Player.h
 * Author: jacob
 *
 * Created on October 20, 2014, 1:36 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "Spell.h"
#include "Entity.h"

#define MAX_SPELL_COUNT 2

class Player : public Entity{
public:
    Player(float, float);
    Player(const Player& orig);
    void move(int x, int z);
    void draw(float);
    virtual ~Player();
private:
};

#endif	/* PLAYER_H */

