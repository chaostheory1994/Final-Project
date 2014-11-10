/* 
 * File:   Spell.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 1:37 PM
 */

#include "Spell.h"

Spell::Spell() {
}

Spell::Spell(const Spell& orig) {
}

Spell::~Spell() {
}

bool Spell::isCD(unsigned long long t){
    return (t >= next_cast);
}
int Spell::cast(Spell_Details* sd, unsigned long long t){ return -1; }
void Spell::update(){ return; }
void Spell::complete(){ return; }
void Spell::draw(float){ return; }
void Spell::dispatch_collision(Entity*){ return; }
Collision_Det* Spell::get_collision_details(){ return cd; }
