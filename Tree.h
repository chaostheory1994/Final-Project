#ifndef TREE_H
#define	TREE_H
#include "Drawable.h"

class Tree : public Drawable{
public:
    Tree(float, float);
    Tree(const Tree& orig);
    void draw();
    virtual ~Tree();
private:

};

#endif	/* TREE_H */