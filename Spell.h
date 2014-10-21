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
    virtual int cast();
    virtual void update();
    virtual void travel();
    virtual void complete();
    virtual void draw(float);
    std::string* get_name();
    void set_name(std::string*);
private:
    std::string* name;
};

#endif	/* SPELL_H */

