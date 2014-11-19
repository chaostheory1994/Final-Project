/* 
 * File:   LittleGrass.cpp
 * Author: jacob
 * 
 * Created on November 19, 2014, 12:39 PM
 */

#include "LittleGrass.h"
#include "Defines.h"
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

LittleGrass::LittleGrass(float x, float z) {
    worldX = x;
    worldZ = z;
}

LittleGrass::LittleGrass(const LittleGrass& orig) {
}

LittleGrass::~LittleGrass() {
}

void LittleGrass::draw(){
    glScalef(0.5, 0.5, 0.5);
    
    glColor3f( 0.0, 0.75, 0.0);
    
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(0.25, 0.0, 0.0);
    glVertex3f(-0.25, 0.0, 0.0);
    glEnd();
}

