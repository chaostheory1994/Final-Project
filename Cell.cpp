/* 
 * File:   Cell.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 11:42 PM
 */

#include "Cell.h"
#include "Defines.h"
#include <cstdlib>

Cell::Cell(int s) {
    size = s;
    first = NULL;
}

Cell::Cell(const Cell& orig) {
    
}

/* Deconstructor */
// Delete all Entities and Spells.
Cell::~Cell() {
    
}

/* Simple data access method */
int Cell::get_size(){
    return size;
}

/* Will draw the cell and all the entities inside it.
 * Even though the player inherits entity it wont be tacked by Cells.  */
void Cell::draw(float i){
    // Start of by drawing the ground.
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON)
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, 0, 0);
    glEnd();
}

