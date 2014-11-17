/* 
 * File:   UIBaseLeft.h
 * Author: jacob
 *
 * Created on November 13, 2014, 12:30 PM
 */

#ifndef UIBASELEFT_H
#define	UIBASELEFT_H
#include "Map.h"

class UIBaseLeft {
public:
    UIBaseLeft();
    UIBaseLeft(const UIBaseLeft& orig);
    virtual ~UIBaseLeft();
    // 2 simple methods to override.
    // What will be drawn to its section of the screen?
    virtual void draw();
    // This is the event the main loop will give in the event of clicking
    // On this UI.
    virtual void interact(int, int);
    // This is the draw size.
    // For ease, I will be setting UI drawing to ortho2d.
    // As such, I will let the UI know what its bounds are.
    // As such you can dynamically resize things if needed.
    // Or just throw it on there however.
    int getID();
    void set_draw_size(int, int);
    void set_map_ptr(Map*);
protected:
    int id;
    int width;
    int height;
    Map* map;
};

#endif	/* UIBASELEFT_H */

