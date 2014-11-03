/* 
 * File:   Cell.h
 * Author: jacob
 *
 * Created on October 20, 2014, 11:42 PM
 */

#ifndef CELL_H
#define	CELL_H

#include "Entity.h"
#include "Spell.h"
#include <queue>

struct Entity_List {
    Entity* e;
    Entity_List* next;
};
struct Spell_List {
    Spell* s;
    Spell_List* next;
};
struct Queue_Packet {
    int obj_type;
    int offset_x;
    int offset_y;
    void* obj;
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
    void update_movement();
    int get_size();
private:
    int size;
    Entity_List* first;
    int wbx, wbz;
    std::queue<Queue_Packet*> q;
};

#endif	/* CELL_H */

