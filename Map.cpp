/* 
 * File:   Map.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 11:26 PM
 */

#include "Map.h"
#include "GL/glut.h"
#include "Cell.h"
#include "Entity.h"

Map::Map(int x, int z) {
    // For now this will represent a simple grey ground.
    // For setting up a simple map, the size will be number of cells
    // Simple 2D array will be setup. 
    sizeX = x;
    sizeZ = z;
}

Map::Map(const Map& orig) {
}

Map::~Map() {
}

void Map::draw(){
    
}

/* Will call update on all the cells.
 * This will also update all the cell's Entities / Spells */
void Map::update(){
    
}

