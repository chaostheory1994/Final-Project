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
    void move(float, float);
    void update();
    void draw(float);
    void update_pos();
    //void map_outbound(int);
    virtual ~Player();
private:
};

#endif	/* PLAYER_H */

