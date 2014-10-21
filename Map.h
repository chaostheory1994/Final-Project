/* 
 * File:   Map.h
 * Author: jacob
 *
 * Created on October 20, 2014, 11:26 PM
 */

#ifndef MAP_H
#define	MAP_H

#define CELL_SIZE 100

#include "Entity.h"
#include "Cell.h"
#include <cstdlib>

class Map {
public:
    Map(int, int);
    Map(const Map& orig);
    virtual ~Map();
    void draw();
    void set_player(Entity* p);
    void update();
private:
    int sizeX;
    int sizeZ;
    Cell** cells; 
    Entity* player;
};

#endif	/* MAP_H */

