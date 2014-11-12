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
struct Collidable_List{
    
};
struct Scenery_List{
    
};

class Cell {
public:
    Cell(int, int, int);
    Cell(const Cell& orig);
    virtual ~Cell();
    void add_entity(Entity*);
    void add_spell(Spell*);
    void remove_entity(Entity*);
    void remove_entity(int);
    void draw(float, int, int);
    void update();
    void update_movement();
    int get_size();
    static bool que_empty();
    static Entity* que_front();
    static void que_pop();
    static bool slque_empty();
    static Spell* slque_front();
    static void slque_pop();
    static bool is_colliding(Collision_Det*, Collision_Det*);
private:
    static std::queue<Entity*> xfer_ent_que;
    static std::queue<Spell*> xfer_spell_que;
    Entity_List* delete_node(Entity_List*);
    Spell_List* delete_node(Spell_List*);
    void check_col_ent(Entity*, Entity*);
    void check_col_sp(Entity*, Spell*);
    //void transfer_entity(Entity*);
    int size;
    Entity_List* first;
    Spell_List* spFirst;
    int wbx, wbz;
};



#endif	/* CELL_H */

