/* 
 * File:   Player.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 1:36 PM
 */

#define _USE_MATH_DEFINES
#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <stdlib.h>
#else
#include <GL/glut.h>
#endif
#include "Player.h"
#include "Spell.h"
#include "Cell.h"
#include "Defines.h"
#include <cmath>
#include <cstdio>

/* Constructor for the player
 * Will take the x,z coordinate in the world
 */
Player::Player(float beginX, float beginZ) {
    // First we set which cell the player will be in.
    x = beginX;
    z = beginZ;
    
    dx = 0;
    dz = 0;
    distX = 0;
    distZ = 0;
    
    shape = gluNewQuadric();
    
    gluQuadricNormals(shape, GLU_SMOOTH);   // Create Smooth Normals ( NEW )
    gluQuadricTexture(shape, GL_TRUE);      // Create Texture Coords ( NEW )
} 

Player::Player(const Player& orig) {
}

Player::~Player() {
    
}

/* Using default map bound algorithm */
//void Player::map_outbound(int id){ printf("Calling player map_bound\n"); }

/* The method that will draw the player when called.
 * The method assumes the player has been translated where he needs to be. */
void Player::draw(){
    // Two States of existence! Deep.
    // Moving or not moving
    if(dx == 0 && dz == 0){
        
    }
    else{
        
    }
    glColor3f(0.30, 0.39, 0.56);
    glRotatef(-direction * (180/M_PI), 0, 1.0, 0); 
    // Legs
    glPushMatrix();
    glTranslatef(0.0, 1.5, 0.0);
    glScalef(1.0, 6.0, 1.0);
    glTranslatef(0.0, 0.0, -0.25);
    gluSphere(shape, 0.25f, 32, 32);
    glTranslatef(0.0, 0.0, 0.5);
    gluSphere(shape, 0.25f, 32, 32);
    glPopMatrix();
    // Body
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 2.25, 0.0);
    glScalef(1, 2, 1);
    gluSphere(shape, 0.5f, 32, 32);
    glPopMatrix();
    glColor3f(1, 1, 1);
    // Head
    glPushMatrix();
    glTranslatef(0.0, 3.5, 0.0);
    glScalef(1, 1.12, 1);
    gluSphere(shape, 0.3, 32, 32);
    glPopMatrix();
    // Arms
    glPushMatrix();
    glTranslatef(0.0, 2.75, 0.0);
    glScalef(1, 1, 4);
    gluSphere(shape, 0.25, 32, 32);
    glPopMatrix();
    /*glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.5, 0, 0);
    glVertex3f(-0.5, 0, -0.5);
    glVertex3f(-0.5, 0, 0.5);
    glEnd();*/
}

/* A method to update the player per SKIP_TICKS */
void Player::update(){
    
}

/* A method to update the player's position per SKIP_TICKS */
void Player::update_pos(){
    // Do player movement.
    if(fabs(distX) <= fabs(dx)){
        x += distX;
        distX = 0;
        dx = 0;
    }
    else{
        distX -= dx;
        x += dx;
    }
    if(fabs(distZ) <= fabs(dz)){
        z += distZ;
        distZ = 0;
        dz = 0;
    }
    else{
        distZ -= dz;
        z += dz;
    }
}

/* This will setup the movement for update to use.
   We have a speed setup in #Defines 
   We need to calculate a dx and dz from the current position.*/
void Player::move(float px, float pz){
    if(px == 0.0f && pz == 0.0f) return;
    // Special Case px = 0;
    if(px == 0.0f)
        direction = (M_PI / 2.0f) * (pz / abs(pz));
    else if(pz == 0.0f && px < 0.0f) direction = M_PI;
    else if(pz == 0.0f) direction = 0.0;
    else if(px < 0.0f && pz > 0.0f) direction = M_PI + atan(pz/px);
    else if(px < 0.0f && pz < 0.0f) direction = -M_PI + atan(pz/px);
    else direction = atan(pz / px);
#ifdef DEBUG_MESSAGES
    printf("Player Direction: %f\n", direction);
#endif
    
    dx = cos(direction) * PLAYER_DEFAULT_SPEED;
    dz = sin(direction) * PLAYER_DEFAULT_SPEED;
#ifdef DEBUG_MESSAGES
    printf("Player Speed: %f, %f\n", dx, dz);
#endif
    distX = px;
    distZ = pz;
#ifdef DEBUG_MESSAGES
    printf("Player Moving: %f, %f\n", distX, distZ);
#endif
}
