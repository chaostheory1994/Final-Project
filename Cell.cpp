/* 
 * File:   Cell.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 11:42 PM
 */

#include "Cell.h"
#include "Defines.h"
#include <cstdlib>
#include <cstdio>
#include <GL/glut.h>

std::queue<Entity*> Cell::xfer_ent_que;

/* This is the constructor for the cells.
 * 3 ints must be provided.
 * s: The size of the cell.
 * wx, wz: The World Coordinate of the cell.*/
Cell::Cell(int s, int wx, int wz) {
    size = s;
    wbx = wx * s;
    wbz = wz * s;
    
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
void Cell::draw(float i, int x, int z){
    Entity_List* curr = first;
    // Start of by drawing the ground.
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, 0, 0);
    glEnd();
    // Debug draw to show where cells end.
#ifdef DEBUG_MESSAGES
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, 0, 0);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(size/16, 0, 0);
    glVertex3f(size/16, 0, size/16);
    glEnd();
#endif
    while(curr != NULL){
        glPushMatrix();
        glTranslatef(curr->e->getX() - (size * x), 0, curr->e->getZ() - (size * z));
        curr->e->draw(i);
        glPopMatrix();
        curr = curr->next;
    }
}

void Cell::add_entity(Entity* e){
    if(first == NULL){
        first = new Entity_List;
        first->e = e;
        first->next = NULL;
    }
    else{
        Entity_List* curr = first;
        while(curr->next != NULL) curr = curr->next;
        curr->next = new Entity_List;
        curr = curr->next;
        curr->e = e;
        curr->next = NULL;
    }
}

/* Will go ahead and update all the entities in the cell.
 * Will also initialize the movement of spells. */
void Cell::update(){
    Entity_List* Ebegin;
    // Lets do collision stuff!
    // Generate a list of Entities on surrounding Cells.
}

/* Delete a node in the list and return the next node.*/
Entity_List* Cell::delete_node(Entity_List* el){
    Entity_List* prev = NULL;
    Entity_List* curr = first;
    /* Find where the node is located. */
    while(curr != el && curr != NULL){
        prev = curr;
        curr = curr->next;
    }
    // Did we find the node?
    if(curr == NULL) return NULL;
    
    // Since we did.
    // Was the node in the first spot?
    if(prev == NULL){
        prev = curr->next;
        delete curr;
        first = prev;
        curr = prev;
    }
    else{
        prev->next = curr->next;
        delete curr;
        curr = prev->next;
    }
    return curr;
}

/* Update all the entities movement*/
void Cell::update_movement(){
    Entity_List* curr = first;
    
    while(curr != NULL) {
        curr->e->update_pos();
        // We need to check if we need to move an entity to a neighbor cell.
        if(curr->e->getX() >= wbx + 100 ||
                curr->e->getX() < wbx ||
                curr->e->getZ() >= wbz + 100 ||
                curr->e->getZ() < wbz) {
            xfer_ent_que.push(curr->e);
            curr = delete_node(curr);
        }
        else curr = curr->next;
    }
}

/* Wrapper Functions for the queue */
bool Cell::que_empty(){
    return xfer_ent_que.empty();
}

Entity* Cell::que_front(){
    return xfer_ent_que.front();
}

void Cell::que_pop(){
    xfer_ent_que.pop();
}
