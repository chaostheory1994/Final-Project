/* 
 * File:   Defines.h
 * Author: jacob
 *
 * Created on October 21, 2014, 10:56 AM
 */

#ifndef DEFINES_H
#define	DEFINES_H

#define DEBUG_MESSAGES
#define CELL_SIZE 100 /* meters / pixels. May Still need adjustment.*/
#define PLAYER_DEFAULT_SPEED 1 /* m/s */
#define GHOST_DEFAULT_SPEED .05 /* m/s */
#define CAMERA_HEIGHT 50
#define JAVA_IS_BUTT
#define UPDATE_RADIUS 37 /* Updates the cells in a square this big around player. */
#define DRAW_RADIUS 11 /* Draws only this big of a square around the player. */
#define GAME_UPDATE_SPEED 25 /* in fps, how many times a second the game should update. */

const int SKIP_TICKS = 1000 / GAME_UPDATE_SPEED;
const int FPS_SKIP_TICKS = 1000;

float get_fps();

/* Collision Macros */
#define BOX_COL 0x1 /* Box */
#define SPHERE_COL 0x2 /* Sphere */
#define CONE_COL 0x3 /* Cone */
#define CYL_COL 0x4 /* Cylinder */
/* Collision Struct*/
/* This struct is here to tell the map/cells how it will go about calculating collision.
 * We will use a very estimated colision that is usually used only to see if objects are
 * are close enough to check for more refined/expensive collision. For our game,
 * using only the first pass collision detection should be enough, especially if
 * the shapes are easy and supported.
 * The values in the struct are going to be used differently between methods.
 * All the methods are defined by the type variable. The macros right above this,
 * are the different types. box, sphere, cone, cylinder.
 * All these shapes are going to be treated like that are alligned with the world.
 * 
 * Box:
 *      pos will be defined as the center of one of the squares.
 *      value is going to be defined as the center of the other square.
 *      dist the size of the all the square's sides on both ends.
 * Sphere:
 *      pos is going to be the center of the sphere. 
 *      value is going to be unused in this method.
 *      dist is the radius of the sphere.
 * Cone:
 *      pos is going to be the point of the cone.
 *      value is going to be the direction of the cone.
 *      dist is going to be the degrees from each end of the cone.
 * Cylinder:
 *      pos is going to be the center of one of the circles at the end. pref bottom.
 *      value is going to be the center of the other end of the cylinder.
 *      dist is the radius of both circles.
 * 
 */
struct Collision_Det{
    int type;
    float pos[3];
    float value[3];
    float dist;
};

/* These are special map bound collision */
#define OUTBOUND_TOP 0x01
#define OUTBOUND_BOTTOM 0x02
#define OUTBOUND_LEFT 0x03
#define OUTBOUND_RIGHT 0x04

// Spell Stuff
// Global Cooldown
#define GLOBAL_COOLDOWN 1.5
#define IGNORE_COOLDOWN 0

#endif	/* DEFINES_H */

