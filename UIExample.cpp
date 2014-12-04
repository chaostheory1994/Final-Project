/* 
 * File:   UIExample.cpp
 * Author: jacob
 * 
 * Created on November 13, 2014, 1:35 PM
 */

#define _CRT_SECURE_NO_WARNINGS
#include "UIExample.h"
#include "Map.h"
#include "Defines.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

UIExample::UIExample() {
    id = 1;
    mousex = 0;
    mousey = 0;
}

UIExample::UIExample(const UIExample& orig) {
}

UIExample::~UIExample() {
}

void UIExample::draw(){
    char str_buff[10];
    int len;
    int i;
    int x, y;
    float fps = get_fps();
    const char* fps_label = "fps: ";
    
    // Time to draw this panel. Lets set a different color.
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(0, height, 0);
    glVertex3f(width, height, 0);
    glVertex3f(width, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    
    // Next lets draw our information
    glPushMatrix();
    // First is fps
    if(fps > 30.0)glColor3f(0.0, 1.0, 0.0);
    else glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(1.0, height - 20.0);
    sprintf(str_buff, "%5.2f", fps);
    len = strlen(fps_label);
    for( i = 0; i < len; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, fps_label[i]);
    }
    // Get length of the string.
    len = strlen(str_buff);
    // Now to draw it to the screen THX GLUT!
    for( i = 0; i < len; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, str_buff[i]);
    }
    
}

void UIExample::interact(int x, int y){
    mousex = x;
    mousey = y;
}

