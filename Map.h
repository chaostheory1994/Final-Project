/* 
 * File:   Map.h
 * Author: jacob
 *
 * Created on October 20, 2014, 11:26 PM
 */

#ifndef MAP_H
#define	MAP_H

#include "Entity.h"
#include "Cell.h"
#include "Drawable.h"
#include <cstdlib>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Map {
public:
    Map(int, int);
    Map(const Map& orig);
    virtual ~Map();
    void draw();
    void set_player(Entity*);
    void add_entity(Entity*);
    int add_spell(Spell*, Entity*, unsigned long long t);
    int add_spell(Spell*, Entity*, float*, unsigned long long t);
    void update();
    int getSizeX();
    int getSizeZ();
    void update_movement();
    void recell_entity(Entity*);
    void update_mouse(int x, int y);
    static Map* get_current_map();
    /*  Gets the current player         */
    Entity* get_current_player();
    void get_mouse(int*, int*);
    /** Getter method for entity's/speels/scenary to get a texture */
    GLuint get_texture(int);
    
private:
    /* These two methods are to populate the world with object/scenery. */
    /* Add scenery will be done by me. You just call it with ur object and
     * it should be placed in the world where u want it. */
    void add_scenery(Drawable*);
    /* This is where u initialize all the different objects and their locations 
     * and where u all add_scenery(Drawable*) to add them to the world. 
     * This method will be called in the constructor of the map and only once. */
    void populate_world();
    /* This is were all textures are loaded from files and inserted to the maps
        Global textures array which will hold all textures.  Called at map creation.
        All associated entities/scenary should be able to access the textures they need from the map somehow */
    void init_textures();
    /* Rebecca Hwa's function found in main.c of texture.zip package */
    void bmp2rgb(GLubyte *, int size);
    void load_bmp(char *fname, GLubyte img[], int size, GLuint *ptname);
    
    
    int sizeX;
    int sizeZ;
    int mouseX, mouseY;
    static Map* currmap;
    Cell*** cells; 
    Entity* player;
    GLuint* tex_names;
};

#endif	/* MAP_H */

