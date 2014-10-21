/* 
 * File:   Spell.h
 * Author: jacob
 *
 * Created on October 20, 2014, 1:37 PM
 */

#ifndef SPELL_H
#define	SPELL_H
#include <string>

class Spell {
public:
    Spell();
    Spell(const Spell& orig);
    virtual ~Spell();
    int cast();
    void draw();
    std::string get_name();
private:

};

#endif	/* SPELL_H */

