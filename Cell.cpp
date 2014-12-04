/* 
 * File:   Cell.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 11:42 PM
 */

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Cell.h"
#include "Defines.h"
#include "Drawable.h"
#include <cstdlib>
#include <cstdio>
#include <queue>

std::queue<Entity*> Cell::xfer_ent_que;
std::queue<Spell*> Cell::xfer_spell_que;

/* This is the constructor for the cells.
 * 3 ints must be provided.
 * s: The size of the cell.
 * wx, wz: The World Coordinate of the cell.*/
Cell::Cell(int s, int wx, int wz) {
    size = s;
    wbx = wx * s;
    wbz = wz * s;

    first = NULL;
    spFirst = NULL;
    scFirst = NULL;
}

Cell::Cell(const Cell& orig) {

}

/* Deconstructor */
// Delete all Entities and Spells.

Cell::~Cell() {

}

/* Simple data access method */
int Cell::get_size() {
    return size;
}

/* Will draw the cell */
void Cell::draw(float i, int x, int z) {
    //int count = 0;
    
    // Start of by drawing the ground.
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
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
    glVertex3f(size / 16, 0, 0);
    glVertex3f(size / 16, 0, size / 16);
    glEnd();
#endif
    
}

/* This will draw the entities after all the landscape has been drawn. 
 * This will fix the bug that occurs when an object isnt quite at the next */
void Cell::draw_objects(float i, int x, int z){
    Entity_List* curr = first;
    Spell_List* spCurr = spFirst;
    Scenery_List* scCurr = scFirst;
    
    // Draw Scenery;
    while(scCurr != NULL){
        glPushMatrix();
        glTranslatef(scCurr->obj->getX() - (size * x), 0, scCurr->obj->getZ() - (size * z));
        scCurr->obj->draw();
        glPopMatrix();
        scCurr = scCurr->next;
    }
    
    while (curr != NULL) {
        glPushMatrix();
        glTranslatef(curr->e->getX() - (size * x), 0, curr->e->getZ() - (size * z));
        curr->e->draw();
        glPopMatrix();
        curr = curr->next;
    }
    while(spCurr != NULL){
        glPushMatrix();
        glTranslatef(spCurr->s->getX() - (size * x), 0, spCurr->s->getZ() - (size * z));
        spCurr->s->draw();
        glPopMatrix();
        spCurr = spCurr->next;
    }
}

void Cell::add_entity(Entity* e) {
    if (first == NULL) {
        first = new Entity_List;
        first->e = e;
        first->next = NULL;
    } else {
        Entity_List* curr = first;
        while (curr->next != NULL) curr = curr->next;
        curr->next = new Entity_List;
        curr = curr->next;
        curr->e = e;
        curr->next = NULL;
    }
}

void Cell::add_spell(Spell* s){
    if( spFirst == NULL){
        spFirst = new Spell_List;
        spFirst->s = s;
        spFirst->next = NULL;
    }
    else{
        Spell_List* curr = spFirst;
        while (curr->next != NULL) curr = curr->next;
        curr->next = new Spell_List;
        curr = curr->next;
        curr->s = s;
        curr->next = NULL;
    }
}

/* Will go ahead and update all the entities in the cell.
 * Will also initialize the movement of spells. */
void Cell::update() {
    // Since collision is depreicated at the moment,
    // This will simply iterate though the entities' update().
    Entity_List* curr = first;
    while( curr != NULL){
        curr->e->update();
        curr = curr->next;
    }
}

/* Delete a node in the list and return the next node.*/
Entity_List* Cell::delete_node(Entity_List* el) {
    Entity_List* prev = NULL;
    Entity_List* curr = first;
    /* Find where the node is located. */
    while (curr != el && curr != NULL) {
        prev = curr;
        curr = curr->next;
    }
    // Did we find the node?
    if (curr == NULL) return NULL;

    // Since we did.
    // Was the node in the first spot?
    if (prev == NULL) {
        prev = curr->next;
        delete curr;
        first = prev;
        curr = prev;
    } else {
        prev->next = curr->next;
        delete curr;
        curr = prev->next;
    }
    return curr;
}

/* Delete a node in the list and return the next node.*/
Spell_List* Cell::delete_node(Spell_List* sp) {
    Spell_List* prev = NULL;
    Spell_List* curr = spFirst;
    /* Find where the node is located. */
    while (curr != sp && curr != NULL) {
        prev = curr;
        curr = curr->next;
    }
    // Did we find the node?
    if (curr == NULL) return NULL;

    // Since we did.
    // Was the node in the first spot?
    if (prev == NULL) {
        prev = curr->next;
        delete curr;
        spFirst = prev;
        curr = prev;
    } else {
        prev->next = curr->next;
        delete curr;
        curr = prev->next;
    }
    return curr;
}

/* Update all the entities movement*/
void Cell::update_movement() {
    Entity_List* curr = first;
    Spell_List* slCurr = spFirst;

    while (curr != NULL) {
        curr->e->update_pos();
        // We need to check if we need to move an entity to a neighbor cell.
        if (curr->e->getX() >= wbx + 100 ||
                curr->e->getX() < wbx ||
                curr->e->getZ() >= wbz + 100 ||
                curr->e->getZ() < wbz) {
            xfer_ent_que.push(curr->e);
            curr = delete_node(curr);
        } else curr = curr->next;
    }
    
    while (slCurr != NULL) {
        slCurr->s->update();
        if(slCurr->s->isComplete()){
            delete slCurr->s;
            slCurr = delete_node(slCurr);
        }
        else{
            // We need to check if we need to move an entity to a neighbor cell.
            if (slCurr->s->getX() >= wbx + 100 ||
                    slCurr->s->getX() < wbx ||
                    slCurr->s->getZ() >= wbz + 100 ||
                    slCurr->s->getZ() < wbz) {
                xfer_spell_que.push(slCurr->s);
                slCurr = delete_node(slCurr);
            } else slCurr = slCurr->next;
        }
    }
}

/* Wrapper Functions for the queue */
bool Cell::que_empty() {
    return xfer_ent_que.empty();
}

Entity* Cell::que_front() {
    return xfer_ent_que.front();
}

void Cell::que_pop() {
    xfer_ent_que.pop();
}

bool Cell::slque_empty(){
    return xfer_spell_que.empty();
}

Spell* Cell::slque_front(){
    return xfer_spell_que.front();
}

void Cell::slque_pop(){
    xfer_spell_que.pop();
}

void Cell::add_scenery(Drawable* obj){
    Scenery_List* temp = scFirst;
    scFirst = new Scenery_List;
    scFirst->obj = obj;
    scFirst->next = temp;
}

/* A method that will return true if a collision is occuring between the two details */
bool Cell::is_colliding(Collision_Det* col1, Collision_Det* col2) {
    // This will require two steps.
    // First we see where the in the second detail collision shape is the closest point to the second shape.
    // Then we use that point to ask if there was a collision.
    // Since there are different options for the collision shape, we will need to check for each.
    // The most expensive checks are going to be the cylinder and the square.
    // This is due to their less predictable shape.
    // Sphere will be the easiest.
    if (col2->type == BOX_COL) {
        // What is the nearest point in the box to the other object?
        // First pos is pretty much the base position of the other bounding box.
        // Lets check using that.
        // Is the rectangular sides facing the other object?

    }
    return 0;
}
