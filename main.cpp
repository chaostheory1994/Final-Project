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

#ifdef __WIN32
#include <windows.h>
#endif

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
bool gluInvertMatrix(const float*, float*);

// Variables.
const int SKIP_TICKS = 1000 / GAME_UPDATE_SPEED;
unsigned long long next_game_tick;
unsigned long long next_fps_update;
float interpolation;
int loops;
int width;
int height;
// Game Variables
Player* p;
Map* m;

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
    glutInitWindowSize(800, 600);
    width = 800;
    height = 600;
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
    p = new Player(0, 0);
    m = new Map(100, 100);
    m->set_player(p);
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
#ifdef DEBUG_MESSAGES
        case '1':
            printf("Player Coord: %f, %f\n", p->getX(), p->getZ());
            break;
        case '2':
            p->move(1, 1);
            break;
        case '3':
            p->move(-1, -1);
            break;
#endif
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
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        /* The Following Section is from
         * www.antongerdelan.net/opengl/raycasting.html
         */
        float model[16];
        float proj[16];
        float temp[16];
        float norm;
        // We have to remember that the mouse coordinate does not directly relate to map dist.
        // We have to reverse the graphics pipeline to convert
        // mouse coordinates into world coordinates.
        // We start by normalizing the coordinates.
        // mousex/width would give 0-1 range
        // but we want -1 to 1 range so we multiply by 2
        // to get the range of 2 and then subtrace by one
        // to get the range we want,
        float tempx, tempy, tempz, tempp;
        float x = (2.0f * mousex) / width - 1.0f;
        // the y coordinate is a little different because
        // the origin of the y is from the top left.
        float y = 1.0f - (2.0f * mousey) / height;
        // We dont really have a z axis as of yet
        float z = -1.0f;
        // Next step is to convert the normalized point into
        // Homogeneous clip coordinates.
        float h = 1.0f;
#ifdef DEBUG_MESSAGES
        printf("Original X,Y,Z,P\n%f, %f, %f, %f\n", x, y, z, h);
#endif
        // Now we have a matrix of [x, y, -1, 1]T
        // Next we convert to camera eye coordinates.
        // First we nead the project matrix.
        glGetFloatv(GL_PROJECTION_MATRIX, temp);
        // We need to do the inverse to get the back to the Camera Coordinates.
        gluInvertMatrix(temp, proj);
        // Now we simply multiply our homogeneous coordinates by the inverse.
        tempx = proj[0] * x + proj[4] * y +
                proj[8] * z + proj[12] * h;
        tempy = proj[1] * x + proj[5] * y +
                proj[9] * z + proj[13] * h;
        tempz = proj[2] * x + proj[6] * y +
                proj[10] * z + proj[14] * h;
        tempp = proj[3] * x + proj[7] * y +
                proj[11] * z + proj[15] * h;
#ifdef DEBUG_MESSAGES
        printf("Post Inverse Projection\n%f, %f, %f, %f\n", tempx, tempy, tempz, tempp);
#endif
        // Reverse to the world coordinates.
        glGetFloatv(GL_MODELVIEW_MATRIX, temp);
        // Inverse
        gluInvertMatrix(temp, model);
        // Multiply the inverse and the new matrix.
        x = model[0] * tempx + model[4] * tempy +
                model[8] * tempz + model[12] * tempp;
        y = model[1] * tempx + model[5] * tempy +
                model[9] * tempz + model[13] * tempp;
        z = model[2] * tempx + model[6] * tempy +
                model[10] * tempz + model[14] * tempp;
        h = model[3] * tempx + model[7] * tempy +
                model[11] * tempz + model[15] * tempp;
#ifdef DEBUG_MESSAGES
        printf("Post ModelView\n%f, %f, %f\n", x, y, z);
#endif
        // Now we need to normalize the matix.
        // We dont actually need to normalize since our
        // Map is on the 0 y axis.
        norm = sqrt(x*x+y*y+z*z);
        x /= norm;
        y /= norm;
        z /= norm;
#ifdef DEBUG_MESSAGES
        printf("%f, %f, %f\n", x, y, z);
#endif
        /* End Of Section*/
        
        //p->move(1.0f, 1.0f);
    }
}


void my_display(void) {
    /* clear the buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1, 0, 0);

    /* draw something */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(p->getX(), CAMERA_HEIGHT, p->getZ(),
            p->getX(), 0, p->getZ(),
            0, 0, -1);
    
    m->draw();
    //p.draw(0.0);

    /* buffer is ready */
    glutSwapBuffers();

    return;
}

void my_idle(void) {
    loops = 0;
    while(GetTickCount() > next_game_tick && loops < MAX_FRAME_SKIP){
        // Update Game Stuff
        m->update();
        
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

/* Method Copied From
 * http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
 * Simply inverts a 4x4 matrix. */
bool gluInvertMatrix(const float m[16], float invOut[16])
{
    double inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}