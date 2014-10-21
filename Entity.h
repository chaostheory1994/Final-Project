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
    float getX();
    float getZ();
private:
    float health;
    float resource;
    float x;
    float z;
    int cellX;
    int cellZ;
};

#endif	/* ENTITY_H */

