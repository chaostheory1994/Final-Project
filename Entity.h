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
    void draw(float);
private:

};

#endif	/* ENTITY_H */

