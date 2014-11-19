/*
 * HUD.cpp
 * Author: Nick Habib
 * 11/17/14 @ 1:00 PM
 */

#include "Defines.h"
#include "Entity.h"
#include "HUD.h"
#include "Map.h"
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

HUD::HUD(Map* m, Entity* p) {
	map = m;
	player = p;
}

//https://www.opengl.org/discussion_boards/showthread.php/176481-SOLVED-HUD-overlay
void HUD::draw() {
	//Set up projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
 
	//Set up ortho: (0,0) is bottom-left
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
 
	//Set up modelview
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
 
	//Draw Stuff ------------------------------------------------------------------------- 
	drawInfoPlayer();
	drawMap();
	drawActionBar();
	drawLogs();
	
	//End Draw Stuff -------------------------------------------------------------------------

	//Pop matrix til back to pre-method call state 
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
 
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

//HP & mana bar; top-left
void HUD::drawInfoPlayer() {
	glPushMatrix();
	
	//modifiers for HP/resource bars (as a %); default length is 10% of screen width
	//***allows for bar to be larger than initial max (i.e. hp/resource was somehow increased)
	//**need to get these variables from player once implemented
	float modHP = 0.1f * 0.90f;
	float modR = 0.1f * 1.5f;

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);      // try drawing a quad
		glVertex2f(0.0f, 0.95f);
		glVertex2f(modHP, 0.95f);
		glVertex2f(modHP, 0.925f);
		glVertex2f(0.0f, 0.925f);
	glEnd();
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);      // try drawing a quad
		glVertex2f(0.0f, 0.925f);
		glVertex2f(modR, 0.925f);
		glVertex2f(modR, 0.90f);
		glVertex2f(0.0f, 0.90f);
	glEnd();

	glPopMatrix();
}

//Mini-map; top-right
void HUD::drawMap() {
	glPushMatrix();

	//convert player co-ords from px to cell precision
	int pX = player->getX() / CELL_SIZE;
	int pY = player->getZ() / CELL_SIZE;
	float x = 0.85f;	//x offset for map display (15% from right)
	//increment for drawing the squares
	float modX = 0.1f / map->getSizeX();
	float modY = 0.1f / map->getSizeZ();

	for(int i = 0; i < map->getSizeX(); i++) {
		float y = 0.95f;	//y offset for map display (15% from right)
		for(int j = 0; j < map->getSizeZ(); j++) {
			//make player co-ord square green, all others white
			if(i == pX && j == pY) glColor3f(0.0f, 0.7f, 0.0f);	
			else glColor3f(1.0f, 1.0f, 1.0f);

			glBegin(GL_QUADS);
				glVertex2f(x, y);
				glVertex2f(x + modX, y);
				glVertex2f(x + modX, y - modY);
				glVertex2f(x, y - modY);
			glEnd();

			y -= modY;
		}

		x += modX;
	}

	glPopMatrix();
}

//Spell Bar; bottom-middle
void HUD::drawActionBar() {
	glPushMatrix();
	
	float x = 0.3f;	//x offset (30% from left)
	//arrays for the 4 squares colors (**will be changed, just placeholder)
	//**make into image of the spell instead? maybe support mouse-over tooltip as well?
	float r[] = {1.0f, 1.0f, 0.0f, 0.0f};
	float g[] = {0.0f, 1.0f, 1.0f, 0.0f};
	float b[] = {0.0f, 0.0f, 0.0f, 1.0f};

	for(int i = 0; i < 4; i++) {
		glColor3f(r[i], g[i], b[i]);
		glBegin(GL_QUADS);      // try drawing a quad
			glVertex2f(x, 0.0);
			glVertex2f(x + 0.1f, 0.0);
			glVertex2f(x + 0.1f, 0.1);
			glVertex2f(x, 0.1);
		glEnd();

		x += 0.1f;	//move x to next square (10% right)
	}

	glPopMatrix();
}

//Text logs; bottom left & right
void HUD::drawLogs() {
	glPushMatrix();

	glPopMatrix();
}

//***implement if we have time to support a targeting system
//Show enemy's hp/mana on mouse-over/click); Top-mid
void HUD::drawTarget() {

}

