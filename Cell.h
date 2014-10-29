/* 
 * File:   Cell.h
 * Author: jacob
 *
 * Created on October 20, 2014, 11:42 PM
 */

#ifndef CELL_H
#define	CELL_H

#include "Entity.h"

struct Entity_List {
    Entity* e;
    Entity_List* next;
};

class Cell {
public:
    Cell(int, int, int);
    Cell(const Cell& orig);
    virtual ~Cell();
    void add_entity(Entity*);
    void remove_entity(Entity*);
    void remove_entity(int);
    void draw(float, int, int);
    void update();
    int get_size();
private:
    int size;
    Entity_List* first;
    int wbx, wbz;
};

#endif	/* CELL_H */

