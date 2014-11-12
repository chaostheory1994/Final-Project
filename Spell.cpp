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

float Spell::getX(){ return x; }
float Spell::getY(){ return y; }
float Spell::getZ(){ return z; }
float Spell::getSpeedX(){ return dx; }
float Spell::getSpeedY(){ return dy; }
float Spell::getSpeedZ(){ return dz; }
bool Spell::isComplete(){ return isCompleted; }
Spell* Spell::cast(Spell_Details* sd, unsigned long long t){ return NULL; }
void Spell::update(){ return; }
//void Spell::complete(){ return; }
void Spell::draw(){ return; }
void Spell::dispatch_collision(Entity*){ return; }
Collision_Det* Spell::get_collision_details(){ return cd; }
