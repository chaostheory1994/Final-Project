/* 
 * File:   Drawable.cpp
 * Author: jacob
 * 
 * Created on November 19, 2014, 12:21 PM
 */

#include "Drawable.h"

Drawable::Drawable() {
}

Drawable::Drawable(const Drawable& orig) {
}

Drawable::~Drawable() {
}

void Drawable::set_pos(float x, float z){
    worldX = x;
    worldZ = z;
}

float Drawable::getX(){ return worldX; }
float Drawable::getZ(){ return worldZ; }

void Drawable::draw() { return; }

