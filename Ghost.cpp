//
//  Ghost.cpp
//  finalproject3
//
//  Created by Kyle  on 11/10/14.
//  Copyright (c) 2014 Kyle . All rights reserved.
//

#define _USE_MATH_DEFINES
#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <stdlib.h>
#include <sys/time.h>
#else
#include <GL/glut.h>
#endif
#include "Ghost.h"
#include "Spell.h"
#include "Cell.h"
#include "Lazer.h"
#include "Defines.h"
#include "Map.h"
#include <cmath>
#include <cstdio>
//GLfloat theta;


/* Constructor for the Ghost
 * Will take the x,z coordinate in the world
 */
Ghost::Ghost(float beginX, float beginZ) {
    // First we set which cell the Ghost will be in.
    x = beginX;
    z = beginZ;
    distX = 0;
    distZ = 0;
    dx = 0;
    dz = 0;
    direction = 0;
    //theta = 0;
    readyToFire = FIRING_RATE;
    lazer_ref = new Lazer();
    curr_map = Map::get_current_map();
    curr_player = curr_map->get_current_player();
    isChasing = false;
    drawGhostAttractionRadius = false;


}

Ghost::Ghost(const Ghost& orig) {
}

Ghost::~Ghost() {
    
}

/* Using default map bound algorithm */
//void Ghost::map_outbound(int id){ printf("Calling Ghost map_bound\n"); }

/* The method that will draw the Ghost when called.
 * The method assumes the Ghost has been translated where he needs to be. */
void Ghost::draw(){
    float i, j;
    float numOfSides = (2 * M_PI)/NUM_SIDES_SPHERE;
    float radiusOfAttraction = GHOST_ATTRACTION_RADIUS;
    
    if (drawGhostAttractionRadius) {
        glColor3f(252.0/255.0, 252.0/255.0, 134.0/255.0);
   
        for (i = 0; i < 2 * M_PI; i += numOfSides) {
        glBegin(GL_POLYGON);
        {
            glVertex3f(cosf(i)*radiusOfAttraction, 0.3, sinf(i)*radiusOfAttraction);
            glVertex3f(cosf(i + numOfSides)* radiusOfAttraction, 0.3, sinf(i + numOfSides)*radiusOfAttraction);
            glVertex3f(cosf(i + numOfSides)*(radiusOfAttraction - .5), 0.3, sinf(i + numOfSides)* (radiusOfAttraction - .5));
            glVertex3f(cosf(i)*(radiusOfAttraction - .5), 0.3, sinf(i)* (radiusOfAttraction - .5));
        }
        glEnd();
        }
    }
    
    
    glPushMatrix();
    glRotatef(-direction * (180/M_PI), 0, 1.0, 0);
    glBegin(GL_TRIANGLES);
    
    if (isChasing) {
        glColor3f( 1.0f, 0.0f, 0.0f );
    }
    else
    {
        glColor3f( 0.0f, 1.0f, 0.0f );
    }
    glVertex3f( 0, 2, 0);
    glVertex3f( -0.5, 0, 0.5);
    glVertex3f( 0.5, 0 ,0.5);
    
    glVertex3f( 0, 2, 0 );
    glVertex3f( -0.5, 0, 0.5);
    glVertex3f( -0.5, 0, -0.5);
    
    glVertex3f( 0, 2, 0);
    glVertex3f( 0.5, 0, -0.5);
    glVertex3f( -0.5, 0, -0.5);
    glEnd();
    glColor3f( 1.0f, 1.0f, 1.0f );
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, curr_map->get_texture(ILLUMINATI_FACE_TEX));
    glTexCoord2f(.5, 1); glVertex3f( 0, 2, 0);
    glTexCoord2f(0, 0); glVertex3f( 0.5, 0 , 0.5);
    glTexCoord2f(1, 0); glVertex3f( 0.5, 0, -0.5);
    
    glEnd();
    //glColor4f(1, 1, 1, 1);
    ///glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
     glPopMatrix();
}

/* toggle the testing radius for ghost area of detection for player */
void Ghost::toggleGhostAttractionRadius() {
    drawGhostAttractionRadius = !drawGhostAttractionRadius;
}

/* A method to update the Ghost per SKIP_TICKS */
void Ghost::update(){
    
    //First Make the object prepare firing the lazer
    //It should increment regardless if player is nearby so that when the player gets near, it fires
    if (readyToFire < FIRING_RATE) {
        readyToFire += SKIP_TICKS;
    }
    
    //first Check if player is nearby this object.
    //If the player is, start firing at the player
    if (isPlayerNear()) {
        
        
        if (readyToFire >= FIRING_RATE) {
            readyToFire -= FIRING_RATE;
            fire_Lazer();
        }
        
        //if the Player is nearby chase the player down
        if (!isMoving() || !isChasing){
            
            //raise ghost movement speed because its not near the player
            isChasing = true;
            
            //printf("Is not moving!\n");
            move(curr_player->getX()-x, curr_player->getZ()-z);
        }
       
        
    }
    //If player isnt nearby the objet, then we do passive animation
    //This includes moving randomly, stopping. and freely rotating :)
    else {
        //Lower the ghosts movement speed because it is not near the player
        isChasing = false;
        
        //If the ghost isnt moving move in a random direction
        if (!isMoving()) {
            float moveX, moveZ;
            
            //random direction 0-350 degress
            int r = rand()%360;
            
            //Find out the direction vector of movement
            moveX = cosf(r * (M_PI/180)) * GHOST_PACE_LENGTH;
            moveZ = sinf(r * (M_PI/180)) * GHOST_PACE_LENGTH;
            
#ifdef DEBUG_MESSAGES
            printf("GHOST IS NOT MOVING SO MOVE!!!\nCurrent Position x: %f, z: %f\nMovex: %f movez: %f", x,z,moveX, moveZ);
#endif
            
            
            /*
             Do all checks to make sure we are not out of bounds
             Re adjust the move ment appropriately to copensate for not moving out of bounds
             
             */
            //If x and z would end up being negative, determine which axis is intersected first
            //then readjust according to that value
            if ( ((x + moveX) < 0) && ((z + moveZ) < 0)) {
                
                //t for hitting the z-axis, meaning x=0
                float zAxisT = (-x/moveX);
                //t for hitting the x-axis, meaning z=0
                float xAxisT = (-z/moveZ);
#ifdef DEBUG_MESSAGES
                printf("Ghost Movement makes x and z negative.\n zAxisT: %f, xAxisT: %f \n", zAxisT, xAxisT);
#endif
                
                //if the z-axis is hit first, readjust so the new x=0
                if (zAxisT < xAxisT) {
                    //newY = Py + (-Px * (Dy/Dx))
                    moveZ = (z + (-x * (moveZ/moveX)))-z;
                    moveX = (0 - x);
                    
#ifdef DEBUG_MESSAGES
                    printf("Readjusted because x will be negative \nMovex: %f movez: %f \n", moveX, moveZ);
#endif
                }
                //if the x-axis is hit first, readjust movement so the new z = 0
                else {
                    //newX = Px + (-Py * (Dx/dy))
                    moveX = (x + (-z * (moveX/moveZ))) - x;
                    moveZ = (0 - z);
                    
#ifdef DEBUG_MESSAGES
                    printf("Readjusted because z will be negative \nMovex: %f movez: %f \n", moveX, moveZ);
#endif
                }
                
            }
            else if ((x + moveX) < 0) {
                //newY = Py + (-Px * (Dy/Dx))
                moveZ = (z + (-x * (moveZ/moveX)))-z;
                moveX = (0 - x);
                
#ifdef DEBUG_MESSAGES
                printf("Readjusted because x will be negative \nMovex: %f movez: %f \n", moveX, moveZ);
#endif
            }
            else if((z + moveZ) < 0)
            {
                //newX = Px + (-Py * (Dx/dy))
                moveX = (x + (-z * (moveX/moveZ))) - x;
                moveZ = (0 - z);
                
#ifdef DEBUG_MESSAGES
                printf("Readjusted because z will be negative \nMovex: %f movez: %f \n", moveX, moveZ);
#endif
            }
            
            move(moveX, moveZ);
        }
    }
    
       
    
#ifdef DEBUG_MESSAGES
    //printf("Ghost Location: %f, %f\n", x, z);
#endif
    
}

//Determine if the player is within the entity's sphere of influence
//Occurs when Player(x,y): 0 > x^2 + y^2 - R^2
bool Ghost::isPlayerNear() {
    
    /* first, convert player coords to object coords */
    float relativeX = curr_player->getX() - x;
    float relativeZ = curr_player->getZ() - z;
    
    float circleX = (powf(relativeX,2) - powf(GHOST_ATTRACTION_RADIUS,2));
    float circleZ = (powf(relativeZ,2) - powf(GHOST_ATTRACTION_RADIUS,2));
#ifdef DEBUG_MESSAGES
    printf("-----isPlayerNear-----\n");
    printf("cirleX: %f \n", circleX );
    printf("circleZ: %f\n", circleZ);

#endif
    
    
    return ( (circleX < 0.0) && (circleZ < 0.0));
    
}

/* a method to fire the ghost's lazer. */
void Ghost::fire_Lazer() {
    
    float px, pz, pvx, pvz, pspeed, a, b, c;
    float t = 0;
    /* Predict the Player Movement and fire with a slight lead */
    //Entity* curr_player = curr_map->get_current_player();
    
    /* get current players coordinates*/
    px = curr_player->getX();
    pz = curr_player->getZ();
    
    /* Calculate current players velocity vectors based of its direction and movement speed */
    pvx = curr_player->getSpeedX();
    pvz = curr_player->getSpeedZ();
    
    /* projectile speed */
    pspeed = L_SPEED;
    
    /* Determine How aim projectile */
    /* http://stackoverflow.com/questions/2248876/2d-game-fire-at-a-moving-target-by-predicting-intersection-of-projectile-and-u */
    
    
    a = powf(pvx,2) + powf(pvz, 2) - powf(pspeed, 2);
    b = 2 * ((pvx * (px - x)) + (pvz * (pz - z)));
    c = powf(px - x,2) + powf(pz - z,2);
    
    float discrim = powf(b, 2) - (4 * a * c);
    
    #ifdef DEBUG_MESSAGES
    printf("FIRE LAZER PREDICTION BLOCK!!!\n");
    printf("Player coords: %f, %f \n", px, pz);
    printf("Ghost coords: %f, %f\n", x, z);
    printf("Player direction: %f, %f \n", pvx, pvz);
    printf("Discriminate : %f\n", discrim);
    #endif
    
    if (discrim > 0 ) {
        float t1 = ((-b + sqrtf(discrim))/(2*a));
        float t2 = ((-b - sqrtf(discrim))/(2*a));
        
        #ifdef DEBUG_MESSAGES
        printf("T-values: %f, %f \n", t1, t2);
        #endif
        
        //choose the smallest positive value
        if (t1 < t2 && t1 > 0) {
            t = t1;
        }
        else {
            t = t2;
        }
    }
    else if (discrim == 0) {
        t = ((-b + sqrtf(discrim))/(2*a));
        #ifdef DEBUG_MESSAGES
        printf("T-values: %f \n", t);
        #endif
    }
    else {
        printf("Lazer can't hit \n");
        return;
    }
    
    float dir[] = {((t * pvx) + px)-x, 0, ((t * pvz) + pz)- z};
    curr_map->add_spell(lazer_ref, this, dir, IGNORE_COOLDOWN);
    
    #ifdef DEBUG_MESSAGES
    printf("Firing direction: %f, %f, %f \n", dir[0], dir[1], dir[2]);
    #endif
    
    /* Rotate to fireing direction */
     // Special Case px = 0;
     
     if(dir[0] == 0.0f)
     direction = (M_PI / 2.0f) * (dir[2] / abs(dir[2])); //up or down
     else if(dir[2] == 0.0f && dir[0] < 0.0f) direction = M_PI; //left
     else if(dir[2] == 0.0f) direction = 0.0;            //right
     else if(dir[0] < 0.0f && dir[2] > 0.0f) direction = M_PI + atan(dir[2]/dir[0]); //left-up
     else if(dir[0] < 0.0f && dir[2] < 0.0f) direction = -M_PI + atan(dir[2]/dir[0]);  //left-down
     else direction = atan(dir[2] / dir[0]); //right up or right down
     

}


/* A method to update the Ghost's position per SKIP_TICKS */
void Ghost::update_pos(){
    // Do Ghost movement
    if(abs(distX) <= abs(dx)){
        x += distX;
        distX = 0;
        dx = 0;
    }
    else{
        distX -= dx;
        x += dx;
    }
    if(abs(distZ) <= abs(dz)){
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
void Ghost::move(float px, float pz){
    if (px < .01 && px > -.01)
    {
        px = 0.0;
    }
    if (pz < .01 && pz > -.01) {
        pz = 0.0;
    }
#ifdef DEBUG_MESSAGES
    printf("Moving %f, %f\n", px, pz);
#endif

     if(px == 0.0f && pz == 0.0f) return;
    // Special Case px = 0;
    
    if(px == 0.0f)
        direction = (M_PI / 2.0f) * (pz / abs(pz)); //up or down
    else if(pz == 0.0f && px < 0.0f) direction = M_PI; //left
    else if(pz == 0.0f) direction = 0.0;            //right
    else if(px < 0.0f && pz > 0.0f) direction = M_PI + atan(pz/px); //left-up
    else if(px < 0.0f && pz < 0.0f) direction = -M_PI + atan(pz/px);  //left-down
    else direction = atan(pz / px); //right up or right down
#ifdef DEBUG_MESSAGES
    printf("Ghost Direction: %f\n", direction);
#endif
    
    if (isChasing) {
        dx = cos(direction) * GHOST_CHASE_SPEED;
        dz = sin(direction) * GHOST_CHASE_SPEED;
    }
    else {
        dx = cos(direction) * GHOST_DEFAULT_SPEED;
        dz = sin(direction) * GHOST_DEFAULT_SPEED;
    }
#ifdef DEBUG_MESSAGES
    printf("Ghost Speed: %f, %f\n", dx, dz);
#endif
    distX = px;
    distZ = pz;
#ifdef DEBUG_MESSAGES
    printf("Ghost Moving: %f, %f\n", distX, distZ);
#endif
}

