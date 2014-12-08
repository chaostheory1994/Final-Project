/* 
 * File:   Entity.h
 * Author: jacob
 *
 * Created on October 20, 2014, 1:57 PM
 */

#ifndef ENTITY_H
#define	ENTITY_H
#include "Defines.h"

class Entity {
public:
    Entity();
    Entity(const Entity& orig);
    virtual ~Entity();
    /* Simply draw the ability! */
    virtual void draw();
    /* This will be used to update anything else */
    virtual void update();
    /* This will initialize a move to the object.
     * This will setup animation and end result of the motion.*/
    virtual void move(float, float);
    /* This method is used to update the position of the entity.*/
    virtual void update_pos();
    /* Spell collision is determined by spell. So only need to check Entity */
    virtual void dispatch_collision(Entity*);
    /* This is a special collision dealing with running off the edge of the map.
     * This method is already defined in Entity and will simply
     * make the speed in the appropriate direction 0 and finish the distance
     * Then it will move the Entity back onto the map. 
     * You do not need to override this method unless you want something different to happen of course.
     * If you wish to override, the possible macros that will be passed are in Defines.h 
     * if you do not want to override, all you need to do is ignore it. */
    virtual void map_outbound(int);
    /* This is another override you can choose to ignore. 
     * It is here mainly for spells. When a spell is cast, an entity should stop to cast it. */
    virtual void cancel_movement();
    Collision_Det* get_collision_details();
    float getX();
    float getZ();
    float getSpeedX();
    float getSpeedZ();
    bool isMoving();
protected:
    float health;
    float resource;
    float x;
    float z;
    float direction;
    float distX, distZ;
    float dx, dz;
    int cellx, cellz;
    /* Internal Collision Struct */
    /* To know how to define this look in Defines.h
     * It is here to tell the collision system what type of collision to apply. */
    Collision_Det* cd;
};

#endif	/* ENTITY_H */

