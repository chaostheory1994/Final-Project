#include "Boulder.h"
#include "Defines.h"
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Boulder::Boulder(float x, float z) {
    worldX = x;
    worldZ = z;
}

Boulder::Boulder(const Boulder& orig) {
}

Boulder::~Boulder() {
}

void Boulder::draw(){
    glScalef(4, 4, 4);
    
    glColor3f(0.67, 0.67, 0.0);
    
	//base
    glBegin(GL_QUADS);
    glVertex3f(-0.5, 0.01, 0.0);
    glVertex3f(0.5, 0.01, 0.0);
    glVertex3f(0.35, 0.01, -0.6);
	glVertex3f(-0.2, 0.01, -0.6);
    glEnd();
	
	//top
	glBegin(GL_QUADS);
	glVertex3f(-0.2, 1.0, -0.2);
	glVertex3f(0.2, 1.0, -0.2);
	glVertex3f(0.1, 1.0, -0.4);
	glVertex3f(-0.05, 1.0, -0.4);
	glEnd();

	//front side
	glBegin(GL_QUADS);
	glVertex3f(-0.5, 0.01, 0.0);
	glVertex3f(0.5, 0.01, 0.0);
	glVertex3f(-0.2, 1.0, -0.2);
	glVertex3f(0.2, 1.0, -0.2);
	glEnd();

	//right side
	glBegin(GL_QUADS);
	glVertex3f(0.5, 0.01, 0.0);
    glVertex3f(0.35, 0.01, -0.6);
	glVertex3f(0.2, 1.0, -0.2);
	glVertex3f(0.1, 1.0, -0.4);
	glEnd();

	//back side
	glBegin(GL_QUADS);
	glVertex3f(0.35, 0.01, -0.6);
	glVertex3f(-0.2, 0.01, -0.6);
	glVertex3f(0.1, 1.0, -0.4);
	glVertex3f(-0.05, 1.0, -0.4);
	glEnd();

	//left side
	glBegin(GL_QUADS);
	glVertex3f(-0.5, 0.01, 0.0);
	glVertex3f(-0.2, 0.01, -0.6);
	glVertex3f(-0.05, 1.0, -0.4);
	glVertex3f(-0.2, 1.0, -0.2);
	glEnd();
}
