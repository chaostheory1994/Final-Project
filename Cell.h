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
//#include "Map.h"
#include <queue>

struct Entity_List {
    Entity* e;
    Entity_List* next;
};
struct Spell_List {
    Spell* s;
    Spell_List* next;
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
    static bool que_empty();
    static Entity* que_front();
    static void que_pop();
private:
    static std::queue<Entity*> xfer_ent_que;
    Entity_List* delete_node(Entity_List*);
    void check_col_ent(Entity*, Entity*);
    void check_col_sp(Entity*, Spell*);
    //void transfer_entity(Entity*);
    int size;
    Entity_List* first;
    int wbx, wbz;
};



#endif	/* CELL_H */

