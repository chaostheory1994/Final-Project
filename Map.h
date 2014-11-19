/* 
 * File:   Map.h
 * Author: jacob
 *
 * Created on October 20, 2014, 11:26 PM
 */

#ifndef MAP_H
#define	MAP_H

#include "Entity.h"
#include "Cell.h"
#include "Drawable.h"
#include <cstdlib>

class Map {
public:
    Map(int, int);
    Map(const Map& orig);
    virtual ~Map();
    void draw();
    void set_player(Entity*);
    void add_entity(Entity*);
    int add_spell(Spell*, Entity*, unsigned long long t);
    int add_spell(Spell*, Entity*, float*, unsigned long long t);
    void update();
    int getSizeX();
    int getSizeZ();
    void update_movement();
    void recell_entity(Entity*);
    void update_mouse(int x, int y);
    static Map* get_current_map();
    void get_mouse(int*, int*);
private:
    /* These two methods are to populate the world with object/scenery. */
    /* Add scenery will be done by me. You just call it with ur object and
     * it should be placed in the world where u want it. */
    void add_scenery(Drawable*);
    /* This is where u initialize all the different objects and their locations 
     * and where u all add_scenery(Drawable*) to add them to the world. 
     * This method will be called in the constructor of the map and only once. */
    void populate_world();
    int sizeX;
    int sizeZ;
    int mouseX, mouseY;
    static Map* currmap;
    Cell*** cells; 
    Entity* player;
    
};

#endif	/* MAP_H */

