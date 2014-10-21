/* 
 * File:   Player.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 1:36 PM
 */

#include "Player.h"
#include <GL/glut.h>
#include "Spell.h"

Player::Player(float beginX, float beginZ) {
    x = beginX;
    z = beginZ;
}

Player::Player(const Player& orig) {
}

Player::~Player() {
    
}

int Player::draw(){
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0.5);
    glVertex3f(-0.5, 0, -0.5);
    glVertex3f(0.5, 0, -0.5);
    glEnd();
}

float Player::getX(){
    return x;
}
float Player::getZ(){
    return z;
}