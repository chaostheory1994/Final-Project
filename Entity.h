/* 
 * File:   Entity.h
 * Author: jacob
 *
 * Created on October 20, 2014, 1:57 PM
 */

#ifndef ENTITY_H
#define	ENTITY_H

class Entity {
public:
    Entity();
    Entity(const Entity& orig);
    virtual ~Entity();
    virtual void draw(float);
    virtual void update();
    virtual void move(float, float);
    float getX();
    float getZ();
protected:
    float health;
    float resource;
    float x;
    float z;
    float direction;
    float distX, distZ;
    float dx, dz;
    int cellx, cellz;
};

#endif	/* ENTITY_H */

