//
//  Ghost.cpp
//  finalproject3
//
//  Created by Kyle  on 11/10/14.
//  Copyright (c) 2014 Kyle . All rights reserved.
//

#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <stdlib.h>
#else
#include <GL/glut.h>
#endif
#include "Ghost.h"
#include "Spell.h"
#include "Cell.h"
#include "Defines.h"
#include <cmath>
#include <cstdio>

/* Constructor for the Ghost
 * Will take the x,z coordinate in the world
 */
Ghost::Ghost(float beginX, float beginZ) {
    // First we set which cell the Ghost will be in.
    x = beginX;
    z = beginZ;
}

Ghost::Ghost(const Ghost& orig) {
}

Ghost::~Ghost() {
    
}

/* Using default map bound algorithm */
//void Ghost::map_outbound(int id){ printf("Calling Ghost map_bound\n"); }

/* The method that will draw the Ghost when called.
 * The method assumes the Ghost has been translated where he needs to be. */
void Ghost::draw(float f){
    glColor3f(0.95, 0.95, 0.95);
    //glRotatef(-direction * (180/M_PI), 0, 1.0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(-0.5, 0, 0.5);
    glVertex3f(-0.5, 0, -0.5);
    glEnd();
}

/* A method to update the Ghost per SKIP_TICKS */
void Ghost::update(){
    
}

/* A method to update the Ghost's position per SKIP_TICKS */
void Ghost::update_pos(){
    // Do Ghost movement.
    /*if(abs(distX) <= abs(dx)){
        x += distX;
        distX = 0;
    }
    else{
        distX -= dx;
        x += dx;
    }
    if(abs(distZ) <= abs(dz)){
        z += distZ;
        distZ = 0;
    }
    else{
        distZ -= dz;
        z += dz;
    } */
}

/* This will setup the movement for update to use.
 We have a speed setup in #Defines
 We need to calculate a dx and dz from the current position.*/
void Ghost::move(float px, float pz){
    /* if(px == 0.0f && pz == 0.0f) return;
    // Special Case px = 0;
    if(px == 0.0f)
        direction = (M_PI / 2.0f) * (pz / abs(pz));
    else if(pz == 0.0f && px < 0.0f) direction = M_PI;
    else if(pz == 0.0f) direction = 0.0;
    else if(px < 0.0f && pz > 0.0f) direction = M_PI + atan(pz/px);
    else if(px < 0.0f && pz < 0.0f) direction = -M_PI + atan(pz/px);
    else direction = atan(pz / px);
#ifdef DEBUG_MESSAGES
    printf("Ghost Direction: %f\n", direction);
#endif
    
    dx = cos(direction) * GHOST_DEFAULT_SPEED;
    dz = sin(direction) * GHOST_DEFAULT_SPEED;
#ifdef DEBUG_MESSAGES
    printf("Ghost Speed: %f, %f\n", dx, dz);
#endif
    distX = px;
    distZ = pz;
#ifdef DEBUG_MESSAGES
    printf("Ghost Moving: %f, %f\n", distX, distZ);
#endif */
}
