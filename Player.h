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

class Player : Entity{
public:
    Player(float, float);
    Player(const Player& orig);
    float getX();
    float getZ();
    void move(int x, int z);
    virtual ~Player();
private:
    float x;
    float z;
    float heath;
    float mana;
    int cellX;
    int cellZ;
};

#endif	/* PLAYER_H */

