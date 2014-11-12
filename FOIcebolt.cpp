/* 
 * File:   FOIcebolt.cpp
 * Author: jacob
 * 
 * Created on November 10, 2014, 11:54 AM
 */

#include "FOIcebolt.h"
#include "Defines.h"
#include "Spell.h"
#include "Cell.h"
#include <cmath>
#include <cstdio>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define FOI_DIST 10.0
#define FOI_SPEED 0.5;

FOIcebolt::FOIcebolt() {
}

FOIcebolt::FOIcebolt(float dir, float startX, float startZ){
    // Start off by converting deg to rad for cos and sin.
    float direction_rad = -(dir * M_PI) / 180;
    // This will be just setting up pathing.
    // We already know the starting point.
    x = startX;
    y = 1;
    z = startZ;
    // We already know the direction it is headed.
    direction = dir;
    // We know how fast we want it to travel
    dy = 0;
    dx = cos(direction_rad) * FOI_SPEED;
    dz = sin(direction_rad) * FOI_SPEED;
    // Finally Where is it going?
    distY = 0;
    distX = cos(direction_rad) * FOI_DIST;
    distZ = sin(direction_rad) * FOI_DIST;
    
    isCompleted = false;
    isRef = true;
}

FOIcebolt::FOIcebolt(const FOIcebolt& orig) {
}

FOIcebolt::~FOIcebolt() {
}

void FOIcebolt::update(){
    
    // Do player movement.
    if(fabs(distX) <= fabs(dx)){
        x += distX;
        distX = 0;
    }
    else{
        distX -= dx;
        x += dx;
    }
    if(fabs(distZ) <= fabs(dz)){
        z += distZ;
        distZ = 0;
    }
    else{
        distZ -= dz;
        z += dz;
    }
    if(distZ == 0 && distX == 0) isCompleted = true;
}

void FOIcebolt::draw(){
    glRotatef(direction + 90, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.5);
    glVertex3f(0.25, 0.0, -0.5);
    glVertex3f(-0.25, 0.0, -0.5);
    glEnd();
}

Spell* FOIcebolt::cast(Spell_Details* sd, unsigned long long t){
    // This is the call from the cell to create the active spell.
    // This will pretty much be copying data from the reference into a new version.
    // Except the new version will be registered as a spell. Then we will delete this reference.
    FOIcebolt* ret = new FOIcebolt(direction, x, z);
    // The returned spell is not a reference.
    ret->isRef = false;
    // That is actually it.
    return ret;
}
