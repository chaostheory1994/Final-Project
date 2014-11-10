/* 
 * File:   Spell.h
 * Author: jacob
 *
 * Created on October 20, 2014, 1:37 PM
 */

#ifndef SPELL_H
#define	SPELL_H
#include <string>
#include "Defines.h"
#include "Entity.h"

/* This struct will be given to the constructor so you can
 * setup mechanics appropriately. */
struct Spell_Details{
    bool isRef; /* This is used to tell the spell it hasnt been cast but is just a reference
                 * to cast it from the player or watever. */
    Entity* player;
    float mouse[3]; // x, y, z relative to player.
    float* mouse_release_ptr; /* Not implemented yet */
};

class Spell {
public:
    Spell();
    Spell(const Spell& orig);
    virtual ~Spell();
    virtual int cast(Spell_Details*, unsigned long long);
    virtual void update();
    // virtual void travel();
    virtual void complete();
    virtual void draw(float);
    Collision_Det* get_collision_details();
    /* Abilities cannot collide with each other but can collide with entities.
     * This method will allow you to evaluate what to do when a collision occurs with
     * said entity. */
    virtual void dispatch_collision(Entity*);
    std::string* get_name();
    void set_name(std::string*);
    int get_id();
    bool isCD(unsigned long long);
protected:
    int id;
    std::string* name;
    unsigned long long next_cast;
    int cooldown;
    /* Internal Collision Struct */
    /* To know how to define this look in Defines.h
     * It is here to tell the collision system what type of collision to apply. */
    Collision_Det* cd;
};

#endif	/* SPELL_H */

