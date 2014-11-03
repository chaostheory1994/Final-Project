/* 
 * File:   Player.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 1:36 PM
 */

#include "Player.h"
#include <GL/glut.h>
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
} 

Player::Player(const Player& orig) {
}

Player::~Player() {
    
}

/* The method that will draw the player when called.
 * The method assumes the player has been translated where he needs to be. */
void Player::draw(float f){
    glColor3f(0, 1, 0);
    glRotatef(-direction * (180/M_PI), 0, 1.0, 0); 
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0, 0);
    glVertex3f(-0.5, 0, -0.5);
    glVertex3f(-0.5, 0, 0.5);
    glEnd();
}

/* A method to update the player per SKIP_TICKS */
void Player::update(){
    
}

/* A method to update the player's position per SKIP_TICKS */
void Player::update_pos(){
    // Do player movement.
    if(distX <= abs(dx)){
        x += distX;
        distX = 0;
    }
    else{
        distX -= dx;
        x += dx;
    }
    if(distZ <= abs(dz)){
        z += distZ;
        distZ = 0;
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
    if(px == 0.0f && pz == 0.0f);
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
