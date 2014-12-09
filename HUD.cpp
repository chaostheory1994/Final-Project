/*
* HUD.cpp
* Author: Nick Habib
* 11/17/14 @ 1:00 PM
*/

#include "Defines.h"
#include "Entity.h"
#include "HUD.h"
#include "Map.h"
#include "FrozenOrb.h"
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define ID_FORB 0

HUD::HUD(Map* m, Entity* p) {
	map = m;
	player = p;
	spells[0] = ID_FORB;	//player only has FrozenOrb
	spells[1] = -1;
	spells[2] = -1;
	spells[3] = -1;
}

//switches to ortho2d to draw HUD on top of scene

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
	float modHP = 0.1f * (player->getHealth() / MAX_HEALTH);
	float modR = 0.1f * (player->getResource() / MAX_RESOURCE);





	//health
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);      // try drawing a quad
	glVertex2f(0.0f, 0.95f);
	glVertex2f(modHP, 0.95f);
	glVertex2f(modHP, 0.925f);
	glVertex2f(0.0f, 0.925f);
	glEnd();

	//resource
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);      // try drawing a quad
	glVertex2f(0.0f, 0.925f);
	glVertex2f(modR, 0.925f);
	glVertex2f(modR, 0.90f);
	glVertex2f(0.0f, 0.90f);
	glEnd();

	glDisable(GL_DEPTH_TEST);
	void * font = GLUT_BITMAP_9_BY_15;
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0.0f, 0.93f);
	char* strHP = "HP:";
	for (int i = 0; i < strlen(strHP); i++) {
		glutBitmapCharacter(font, strHP[i]);
	}

	glRasterPos2f(0.0f, 0.90f);
	char* strMana = "Mana:";
	for (int i = 0; i < strlen(strMana); i++) {
		glutBitmapCharacter(font, strMana[i]);
	}
	glEnable(GL_DEPTH_TEST);

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

	for (int i = 0; i < map->getSizeX(); i++) {
		float y = 0.95f;	//y offset for map display (15% from right)
		for (int j = 0; j < map->getSizeZ(); j++) {
			//make player co-ord square green, all others white
			if (i == pX && j == pY) glColor3f(0.0f, 0.7f, 0.0f);
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






	for (int i = 0; i < 4; i++) {
		glColor3f(0.0f, 0.0f, 0.0f);

		glBegin(GL_QUADS);      // try drawing a quad
		glVertex2f(x + 0.001f, 0.001f);
		glVertex2f(x + 0.099f, 0.001f);
		glVertex2f(x + 0.099f, 0.099f);
		glVertex2f(x + 0.001f, 0.099f);
		glEnd();

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		glVertex2f(x, 0.0f);
		glVertex2f(x + 0.1f, 0.0f);
		glVertex2f(x + 0.1f, 0.1f);
		glVertex2f(x, 0.1f);
		glEnd();

		if (spells[i] == ID_FORB) {
			glColor3f(0.0f, 0.0f, 1.0f);
			glTranslatef(x + 0.05f, 0.05f, 0.0f);
			gluSphere(gluNewQuadric(), 0.0249f, 32, 32);
			glTranslatef(-(x + 0.05f), -0.05f, 0.0f);
		}

		x += 0.1f;	//move x to next square (10% right)
	}

	//draw keyboard numbers in top right of ability boxes
	glDisable(GL_DEPTH_TEST);
	void * font = GLUT_BITMAP_9_BY_15;
	glColor3f(1.0f, 1.0f, 1.0f);
	x = 0.38f;
	for (int i = 0; i < 4; i++) {
		glRasterPos2f(x, 0.08f);
		glutBitmapCharacter(font, '2' + i);
		x += 0.1f;

	}
	glEnable(GL_DEPTH_TEST);





	glPopMatrix();
}

//***implement if we have time to support a targeting system
//Show enemy's hp/mana on mouse-over/click); Top-mid
void HUD::drawTarget() {

}

