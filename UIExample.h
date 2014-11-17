/* 
 * File:   UIExample.h
 * Author: jacob
 *
 * Created on November 13, 2014, 1:35 PM
 */

#ifndef UIEXAMPLE_H
#define	UIEXAMPLE_H

#include "UIBaseLeft.h"

class UIExample : public UIBaseLeft{
public:
    UIExample();
    UIExample(const UIExample& orig);
    void draw();
    void interact(int, int);
    virtual ~UIExample();
private:
    int mousex;
    int mousey;
};

#endif	/* UIEXAMPLE_H */

