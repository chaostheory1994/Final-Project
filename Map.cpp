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
#include "Defines.h"


Map::Map(int x, int z) {
    // For now this will represent a simple grey ground.
    // For setting up a simple map, the size will be number of cells
    // Simple 2D array will be setup. 
    int i, j;
    
    sizeX = x;
    sizeZ = z;
    cells = new Cell**[z];
    for(i = 0; i < z; i++){
        cells[i] = new Cell*[x];
        for(j = 0; j < x; j++) cells[i][j] = new Cell(CELL_SIZE);
    }
}

Map::Map(const Map& orig) {
}

Map::~Map() {
}

void Map::draw(){
    int i, j;
    glPushMatrix();
    for( i = 0; i < sizeZ; i++){
        glPushMatrix();
        for(j = 0; j < sizeX; j++){
            cells[i][j]->draw(0.0, j, i);
            glTranslatef(CELL_SIZE, 0, 0);
        }
        glPopMatrix();
        glTranslatef(0, 0, CELL_SIZE);
    }
    glPopMatrix();
    
}

/* Will call update on all the cells.
 * This will also update all the cell's Entities / Spells */
void Map::update(){
    int i, j;
    for(i = 0; i < sizeZ; i++) for(j = 0; j < sizeX; j++) cells[i][j]->update();
}

/* The Player is special and the map will use the reference to the player to
 * Decide certain things like what to draw. */
void Map::set_player(Entity* p){
    player = p;
    cells[(int)(p->getZ() / 100)][(int)(p->getX() / 100)]->add_entity(player);
}

