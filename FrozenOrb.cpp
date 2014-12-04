
/*
 * File:   FrozenOrb.cpp
 * Author: jacob
 * 
 * Created on November 10, 2014, 10:40 AM
 */

#define _USE_MATH_DEFINES
#include "FrozenOrb.h"
#include "Spell.h"
#include "Defines.h"
#include "FOIcebolt.h"
#include <cmath>
#include <cstdio>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Map.h"
#define FO_SPEED 0.25
#define FO_DIST 10.0
#define FO_RAD 0.75


FrozenOrb::FrozenOrb() {
    isRef = true;
    cooldown = GLOBAL_COOLDOWN;
    isCompleted = false;
    //name = "Frozen Orb";
    id = 0;
}

FrozenOrb::FrozenOrb(const FrozenOrb& orig) {
}

FrozenOrb::~FrozenOrb() {
}

/* Setting up a new frozen orb to cast */
Spell* FrozenOrb::cast(Spell_Details* sd, unsigned long long t){
    // Create new generic reference version.
    FrozenOrb* ret = new FrozenOrb;
    float temp;
    
    // Make it 20% cooler by unmaking it a reference verison.
    ret->isRef = false;
    // Now we need to setup its path.
    // First is its initial position.
    ret->x = sd->player->getX();
    ret->z = sd->player->getZ();
    ret->y = 1;
    // Where is it heading?
    // Y is easy
    ret->distY = 0;
    // Now we need to find the distance from the caster to the mouse.
    temp = sqrt((sd->mouse[0] * sd->mouse[0]) + (sd->mouse[2] * sd->mouse[2]));
    // Now we can set the dists by scaling.
    ret->distX = (sd->mouse[0] / temp) * FO_DIST;
    ret->distZ = (sd->mouse[2] / temp) * FO_DIST;
    // Finally how fast is it to be moving?
    // We can do similar function to what we did for dist variables.
    ret->dx = (sd->mouse[0] / temp) * FO_SPEED;
    ret->dy = 0;
    ret->dz = (sd->mouse[2] / temp) * FO_SPEED;
    if(sd->mouse[0] == 0.0f)
        ret->direction = (M_PI / 2.0f) * (sd->mouse[2] / abs(sd->mouse[0]));
    else if(sd->mouse[2] == 0.0f && sd->mouse[0] < 0.0f) ret->direction = M_PI;
    else if(sd->mouse[2] == 0.0f) ret->direction = 0.0;
    else if(sd->mouse[0] < 0.0f && sd->mouse[2] > 0.0f) ret->direction = M_PI + atan(sd->mouse[2]/sd->mouse[0]);
    else if(sd->mouse[0] < 0.0f && sd->mouse[2] < 0.0f) ret->direction = -M_PI + atan(sd->mouse[2]/sd->mouse[0]);
    else ret->direction = atan(sd->mouse[2] / sd->mouse[0]);
    // Make sure direction is in degrees.
    ret->direction = (ret->direction * 180) / M_PI;
    // Setup Quadratic
    ret->shape = gluNewQuadric();
    gluQuadricNormals(ret->shape, GLU_SMOOTH);   // Create Smooth Normals 
    gluQuadricTexture(ret->shape, GL_TRUE);      // Create Texture Coords 
    return ret;
}

/* Lets draw an orb! */
void FrozenOrb::draw(){
    //float i;
    // Just gonna be a circle for now
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0, 2, 0);
    gluSphere(shape, 1.0f, 32, 32);
    /*glBegin(GL_POLYGON);
    for(i = -FO_RAD; i <= FO_RAD; i+=0.15){
        glVertex3f(i, y, sqrt((FO_RAD*FO_RAD) - i*i));
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(i = -FO_RAD; i <= FO_RAD; i+=0.15){
        glVertex3f(i, y, -sqrt((FO_RAD*FO_RAD) - i*i));
    }
    glEnd();*/
}

/* Pretty much the same as Player::update_pos */
void FrozenOrb::update(){
    Map* map;
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
    // Check if the spell took its course.
    if(distZ == 0 && distX == 0) isCompleted = true;
    // the one difference is its ability to create shards.
    // I want the orb to do 2 cycles when it hits the end.
    // First we need to aquire the map ptr.
    map = Map::get_current_map();
    // The method I will be using for creating the shards.
    // I will create a reference version each time I want to make a new one.
    // The reference version will hold the values i need to pass along to the active spell.
    // Since i will not need it more than once i will delete it after.
    // First we need to detect if its time to cast a new bolt.
    // Since we can assume this will occur every SKIPTICK we can do the following calc.
    // I want 2 rotations per cast. the orb moves at 0.5/SKIPTICK speed.
    // The orb moves 10.0 which means there are 20 SKIPTICKS that occur.
    // 2 rotations / 20 SKIPTICKS = 0.1 / SKIPTICK.
    // We will just cast a new bolt every tick.
    direction += 36; // 360 * 0.1 = 36;
    // To make sure things do not break;
    if( direction >= 360 ) direction -= 360;
    // create reference version.
    FOIcebolt* ref = new FOIcebolt(direction, x, z);
    // Ask the map to cast the spell.
    // We dont need any of the the parameters other than the reference parameter.
    map->add_spell(ref, NULL, IGNORE_COOLDOWN);
    delete ref;
}