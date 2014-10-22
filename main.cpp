#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include "Player.h"
#include "Entity.h"
#include "Map.h"
#include "Defines.h"

#define TRUE  1
#define FALSE 0

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define my_assert(X,Y) ((X)?(void) 0:(printf("error:%s in %s at %d", Y, __FILE__, __LINE__), myabort()))

#define DELTA_TIME 10  /* defined to be 10 msec */
#define GAME_UPDATE_SPEED 25 /* in fps, how many times a second the game should update. */
#define MAX_FRAME_SKIP 5 /* Max number of frames that the program can skip to update game mechanics */

void myabort(void);
void glut_setup(void);
void gl_setup(void);
void my_setup(int argc, char **argv);
void my_display(void);
void my_reshape(int w, int h);
void my_keyboard(unsigned char key, int x, int y);
void my_mouse_drag(int x, int y);
void my_mouse(int button, int state, int mousex, int mousey);
void my_idle(void);
#ifdef __linux__
unsigned GetTickCount();
#endif

// Variables.
const int SKIP_TICKS = 1000 / GAME_UPDATE_SPEED;
unsigned long long next_game_tick;
unsigned long long next_fps_update;
float interpolation;
int loops;
int width;
int height;
// Game Variables
Player p(0, 0);
Map m(100, 100);

void myabort(void) {
    abort();
    exit(1); /* exit so g++ knows we don't return. */
}

int main(int argc, char **argv) {
    /* General initialization for GLUT and OpenGL
    Must be called first */
    glutInit(&argc, argv);

    /* we define these setup procedures */
    glut_setup();
    gl_setup();
    my_setup(argc, argv);

    /* go into the main event loop */
    glutMainLoop();

    return (0);
}

/* This function sets up the windowing related glut calls */
void glut_setup(void) {

    /* specify display mode -- here we ask for a double buffer and RGB coloring */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    /* make a 400x300 window with the title of "GLUT Skeleton" placed at the top left corner */
    glutInitWindowSize(400, 300);
    width = 400;
    height = 300;
    glutInitWindowPosition(0, 0);
    glutCreateWindow("GLUT Demo 1");

    /*initialize callback functions */
    glutDisplayFunc(my_display);
    glutReshapeFunc(my_reshape);
    glutMouseFunc(my_mouse);
    glutMotionFunc(my_mouse_drag);
    glutKeyboardFunc(my_keyboard);
    glutIdleFunc(my_idle);


    return;
}

/* This function sets up the initial states of OpenGL related enivornment */
void gl_setup(void) {

    /* specifies a background color: black in this case */
    glClearColor(0, 0, 0, 0);

    /* setup for simple 2d projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* set the viewable portion  */
    gluPerspective(20, width / height, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    return;
}

void my_setup(int argc, char **argv) {
    next_game_tick = GetTickCount();
    next_fps_update = GetTickCount();
    m.set_player(&p);
#ifdef DEBUG_MESSAGES
    // Section for Debug Messages.
#endif
    return;
}

void my_reshape(int w, int h) {
    /* define viewport -- x, y, (origin is at lower left corner) width, height */
    glViewport(0, 0, w, h);
    width = w;
    height = h;
}

/* Sample keyboard callback function.
 This allows the user to quit the program
 by typing the letter q.
 */
void my_keyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 'q':
        case 'Q':
            exit(0);
            break;
        default: break;
    }
    return;
}

/* currently doesn't do anything */
void my_mouse_drag(int x, int y) {
    return;
}

/* stubbed but doesn't do anything either
 (mousex, mousey) are in screen coordinates
 that is, (0,0) is at the upper left corner
 */
void my_mouse(int button, int state, int mousex, int mousey) {
}

void my_display(void) {
    /* clear the buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1, 0, 0);

    /* draw something */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(p.getX(), 50, p.getZ(),
            p.getX(), 0, p.getZ(),
            0, 0, -1);
    
    m.draw();
    //p.draw(0.0);

    /* buffer is ready */
    glutSwapBuffers();

    return;
}

void my_idle(void) {
    loops = 0;
    while(GetTickCount() > next_game_tick && loops < MAX_FRAME_SKIP){
        // Update Game Stuff
        
        
        // Update Timing Stuff
        next_game_tick += SKIP_TICKS;
        loops++;
    }
    
    // Display Screen
    my_display();
    return;
}

#ifdef __linux__

unsigned GetTickCount() {
    timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts)) {
        return 0;
    }
    return ((long long) ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}
#endif