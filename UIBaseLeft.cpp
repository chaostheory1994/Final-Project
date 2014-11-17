/* 
 * File:   UIBaseLeft.cpp
 * Author: jacob
 * 
 * Created on November 13, 2014, 12:30 PM
 */

#include "UIBaseLeft.h"
#include "Map.h"

UIBaseLeft::UIBaseLeft() {
    id = -1;
}

UIBaseLeft::UIBaseLeft(const UIBaseLeft& orig) {
}

UIBaseLeft::~UIBaseLeft() {
}

void UIBaseLeft::set_draw_size(int x, int y){
    width = x;
    height = y;
}
void UIBaseLeft::set_map_ptr(Map* m){ map = m; }

int UIBaseLeft::getID(){ return id; }

void UIBaseLeft::draw(){ return; }
void UIBaseLeft::interact(int x, int y){ return; }
