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
    
};

class Cell {
public:
    Cell(int);
    Cell(const Cell& orig);
    virtual ~Cell();
    void add_entity(Entity* e);
    void remove_entity(Entity* e);
    void remove_entity(int id);
    void draw(float);
    int get_size();
private:
    int size;
    Entity_List* first;
};

#endif	/* CELL_H */

