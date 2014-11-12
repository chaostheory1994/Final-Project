/* 
 * File:   Entity.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 1:57 PM
 */

#include "Entity.h"
#include <cstdio>

Entity::Entity() {
}

Entity::Entity(const Entity& orig) {
}

Entity::~Entity() {
}

void Entity::move(float px, float pz){
    distX = px - x;
    distZ = pz - z;
}

void Entity::map_outbound(int id){
#ifdef DEBUG_MESSAGES
    printf("Calling Super map_bound\n");
#endif
    // There are four places the object can hit the edge at. top, bottom, left, right.
    if(id == OUTBOUND_TOP || id == OUTBOUND_BOTTOM){
        // Reverse the last movement.
        z -= dz;
        // Set movement in that direction to 0.
        dz = 0;
        // Update distZ.
        distZ = 0;
    }
    else if(id == OUTBOUND_LEFT || id == OUTBOUND_RIGHT){
        // Same as above but for x direction.
        x -= dx;
        dx = 0;
        distX = 0;
    }
}

void Entity::cancel_movement(){
    dx = 0;
    dz = 0;
    distX = 0;
    distZ = 0;
}

void Entity:: update_pos(){ return; }
float Entity::getX(){ return x;}
float Entity::getZ(){ return z;}
float Entity::getSpeedX(){ return dx; }
float Entity::getSpeedZ(){ return dz; }
void Entity::draw(){ return; };
void Entity::update(){ return; }
void Entity::dispatch_collision(Entity*){ return; }
Collision_Det* Entity::get_collision_details(){ return cd; }

