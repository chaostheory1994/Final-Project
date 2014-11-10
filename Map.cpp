/* 
 * File:   Map.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 11:26 PM
 */

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Map.h"
#include "Cell.h"
#include "Entity.h"
#include "Defines.h"
#include <queue>

/* Constructor for the map.
 * Paramenters are the number of cells in the x, y*/
Map::Map(int x, int z) {
    // For now this will represent a simple grey ground.
    // For setting up a simple map, the size will be number of cells
    // Simple 2D array will be setup. 
    int i, j;
    
    sizeX = x;
    sizeZ = z;
    cells = new Cell**[x];
    for(i = 0; i < x; i++){
        cells[i] = new Cell*[z];
        for(j = 0; j < z; j++) cells[i][j] = new Cell(CELL_SIZE, i, j);
    }
}

Map::Map(const Map& orig) {
}

Map::~Map() {
}

void Map::draw(){
    int i, j;
    int x = (player->getX() / CELL_SIZE) - (DRAW_RADIUS / 2);
    int z = (player->getZ() / CELL_SIZE) - (DRAW_RADIUS / 2);
    glPushMatrix();
    for(i = 0; i < DRAW_RADIUS && (i + x) < sizeX; i++){
        if((i + x) < 0) continue;
        glPushMatrix();
        for(j = 0; j < DRAW_RADIUS && (j + z) < sizeZ; j++){
            if((j + z) < 0) continue;
            cells[i + x][j + z]->draw(0.0, i + x, j + z);
            glTranslatef(0, 0, CELL_SIZE);
        }
        glPopMatrix();
        glTranslatef(CELL_SIZE, 0, 0);
    }
    glPopMatrix();
    
}

/* Will call update on all the cells.
 * This will also update all the cell's Entities / Spells
 * though checking for collision and whatever other various effect
 * The different objects may need.
 * Should be called before map.update_movement();*/
void Map::update(){
    Entity* Etemp;
    Spell* Stemp;
    int tfer_x, tfer_z;
    
    // Finally Lets ensure the queue is empty and replace all those entities if it isnt.
    while(!Cell::que_empty()){
        Etemp = Cell::que_front();
        Cell::que_pop();
        tfer_x = (int)((Etemp->getX() - CELL_SIZE) / CELL_SIZE);
        tfer_z = (int)((Etemp->getZ() - CELL_SIZE) / CELL_SIZE);
        // Did the entity fall off the edge?
        if(tfer_x < 0){
            // The entity went off the left edge of the map.
            // We need to adjust the Entity to replace it on the map.
            Etemp->map_outbound(OUTBOUND_LEFT);
            tfer_x = -1;
        }
        else if(tfer_x+1 >= sizeX){
            // Right edge.
            Etemp->map_outbound(OUTBOUND_RIGHT);
            tfer_x = (sizeX - 2);
        }
        // Top and bottom now.
        if(tfer_z < 0){
            // Top
            Etemp->map_outbound(OUTBOUND_TOP);
            tfer_z = -1;
        }
        else if(tfer_z+1 >= sizeZ){
            // bottom
            Etemp->map_outbound(OUTBOUND_BOTTOM);
            tfer_z = (sizeZ - 2);
        }
        cells[tfer_x+1][tfer_z+1]->add_entity(Etemp);
    }
    
    // Same thing for the spell queue.
}

/* Will call update on all the cells.
 * Will simple have the cell move all the objects as best as it can.*/
void Map::update_movement(){
    int i, j;
    int x = (player->getX() / CELL_SIZE) - (DRAW_RADIUS / 2);
    int z = (player->getZ() / CELL_SIZE) - (DRAW_RADIUS / 2);
    for(i = 0; i < UPDATE_RADIUS && (i + x) < sizeX; i++){
        if((i + x) < 0) continue;
        for(j = 0; j < UPDATE_RADIUS && (j + z) < sizeZ; j++){
            if((j + z) < 0) continue;
            cells[i + x][j + z]->update_movement();
        }
    }
}
/* The Player is special and the map will use the reference to the player to
 * Decide certain things like what to draw. */
void Map::set_player(Entity* p){
    player = p;
    cells[(int)(p->getX() / 100)][(int)(p->getZ() / 100)]->add_entity(player);
}

/* Add any entity to the map based off the entity's position variables
 * May not be the final function for this purpose but I created it to add a ghost to the map for beta testing */
void Map::add_entity(Entity* p){
    cells[(int)(p->getX() / 100)][(int)(p->getZ() / 100)]->add_entity(p);
}

/* Simple interface for the main loop to have the map keep track of mouse coordinates. */
void Map::update_mouse(int x, int y){
    mouseX = x;
    mouseY = y;
}

/* Adding a spell is a bit complicated since to setup the details, we need to convert mouse to screen coordinates again. */
int Map::add_spell(Spell* sp, Entity* caster, unsigned t){
    Spell_Details* sd;
    // First we check is the spell on cooldown?
    if(!sp->isCD(t)) return -1;
    // We now we have the goto to cast the spell.
    sd = new Spell_Details;
    
    //added because error was thrown that no int was returned
    //return 0;
}