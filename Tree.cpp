#include "Tree.h"
#include "Defines.h"
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Tree::Tree(float x, float z) {
    worldX = x;
    worldZ = z;
}

Tree::Tree(const Tree& orig) {
}

Tree::~Tree() {
}

void Tree::draw(){
	glPushMatrix();
	glScalef(2.0, 12.0, 2.0);
    glColor3f(0.44, 0.23, 0.0);
    glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.0, 0.75, 0.0);
	glTranslatef(0.0, 6.0, 0.0);
	glutSolidSphere(2, 20, 20);
}

