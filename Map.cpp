/* 
 * File:   Map.cpp
 * Author: jacob
 * 
 * Created on October 20, 2014, 11:26 PM
 */

#include "Map.h"
#include "Cell.h"
#include "Entity.h"
#include "Defines.h"
#include "LittleGrass.h"
#include <queue>
#include <cstdlib>

Map* Map::currmap = NULL;
static GLubyte illum24_v2_img[smallWidth*smallWidth*3] ;
/* Constructor for the map.
 * Paramenters are the number of cells in the x, y*/
Map::Map(int x, int z) {
    // For now this will represent a simple grey ground.
    // For setting up a simple map, the size will be number of cells
    // Simple 2D array will be setup. 
    int i, j;
    
    sizeX = x;
    sizeZ = z;
    tex_names = new GLuint [NUM_TEXTURES];
    
    
    cells = new Cell**[x];
    for (i = 0; i < x; i++) {
        cells[i] = new Cell*[z];
        for (j = 0; j < z; j++) cells[i][j] = new Cell(CELL_SIZE, i, j);
    }
    
    init_textures();
    populate_world();
    
    currmap = this;
    
}

Map::Map(const Map& orig) {
}

Map::~Map() {
}

void Map::draw() {
    int i, j;
    int x = (player->getX() / CELL_SIZE) - (DRAW_RADIUS / 2);
    int z = (player->getZ() / CELL_SIZE) - (DRAW_RADIUS / 2);
    // Draw the ground.
    glPushMatrix();
    for (i = 0; i < DRAW_RADIUS && (i + x) < sizeX; i++) {
        if ((i + x) < 0) continue;
        glPushMatrix();
        for (j = 0; j < DRAW_RADIUS && (j + z) < sizeZ; j++) {
            if ((j + z) < 0) continue;
            cells[i + x][j + z]->draw(0.0, i + x, j + z);
            glTranslatef(0, 0, CELL_SIZE);
        }
        glPopMatrix();
        glTranslatef(CELL_SIZE, 0, 0);
    }
    glPopMatrix();
    // Draw the Entities/Spells
    glPushMatrix();
    for (i = 0; i < DRAW_RADIUS && (i + x) < sizeX; i++) {
        if ((i + x) < 0) continue;
        glPushMatrix();
        for (j = 0; j < DRAW_RADIUS && (j + z) < sizeZ; j++) {
            if ((j + z) < 0) continue;
            cells[i + x][j + z]->draw_objects(0.0, i + x, j + z);
            glTranslatef(0, 0, CELL_SIZE);
        }
        glPopMatrix();
        glTranslatef(CELL_SIZE, 0, 0);
    }
    glPopMatrix();
    
    

}

/* Will call update on all the cells.
 * This will also update all the cell's Entities / Spells
 * though checking for collision and whatever other various effect
 * The different objects may need.
 * Should be called before map.update_movement();*/
void Map::update() {
    Entity* Etemp;
    Spell* Stemp;
    int tfer_x, tfer_z;
    int i, j, x, z;
    
    

    // Finally Lets ensure the queue is empty and replace all those entities if it isnt.
    while (!Cell::que_empty()) {
        Etemp = Cell::que_front();
        Cell::que_pop();
        tfer_x = (int) ((Etemp->getX() - CELL_SIZE) / CELL_SIZE);
        tfer_z = (int) ((Etemp->getZ() - CELL_SIZE) / CELL_SIZE);
        // Did the entity fall off the edge?
        if (tfer_x < 0) {
            // The entity went off the left edge of the map.
            // We need to adjust the Entity to replace it on the map.
            Etemp->map_outbound(OUTBOUND_LEFT);
            tfer_x = -1;
        } else if (tfer_x + 1 >= sizeX) {
            // Right edge.
            Etemp->map_outbound(OUTBOUND_RIGHT);
            tfer_x = (sizeX - 2);
        }
        // Top and bottom now.
        if (tfer_z < 0) {
            // Top
            Etemp->map_outbound(OUTBOUND_TOP);
            tfer_z = -1;
        } else if (tfer_z + 1 >= sizeZ) {
            // bottom
            Etemp->map_outbound(OUTBOUND_BOTTOM);
            tfer_z = (sizeZ - 2);
        }
        cells[tfer_x + 1][tfer_z + 1]->add_entity(Etemp);
    }

    // Same thing for the spell queue.
    while (!Cell::slque_empty()) {
        Stemp = Cell::slque_front();
        Cell::slque_pop();
        tfer_x = (int) ((Stemp->getX() - CELL_SIZE) / CELL_SIZE);
        tfer_z = (int) ((Stemp->getZ() - CELL_SIZE) / CELL_SIZE);
        // Did the spell fall off the edge?
        if (tfer_x < 0 || tfer_z < 0 || tfer_x + 1 >= sizeX || tfer_z + 1 >= sizeZ) {
            // The spell went off the edge of the map;
            // we are just going to delete it.
            delete Stemp;
        }
        else cells[tfer_x + 1][tfer_z + 1]->add_spell(Stemp);
    }
    // Call update on all entities. After all movement has been settled.
    x = (player->getX() / CELL_SIZE) - (DRAW_RADIUS / 2);
    z = (player->getZ() / CELL_SIZE) - (DRAW_RADIUS / 2);
    for(i = 0; i < UPDATE_RADIUS && (i + x) < sizeX; i++){
        if((i + x) < 0) continue;
        for(j = 0; j < UPDATE_RADIUS && (j + z) < sizeZ; j++) {
            if((j + z) < 0) continue;
            cells[i+x][j+z]->update();
        }
    }
}

/* Will call update on all the cells.
 * Will simple have the cell move all the objects as best as it can.*/
void Map::update_movement() {
    int i, j;
    int x = (player->getX() / CELL_SIZE) - (DRAW_RADIUS / 2);
    int z = (player->getZ() / CELL_SIZE) - (DRAW_RADIUS / 2);
    for (i = 0; i < UPDATE_RADIUS && (i + x) < sizeX; i++) {
        if ((i + x) < 0) continue;
        for (j = 0; j < UPDATE_RADIUS && (j + z) < sizeZ; j++) {
            if ((j + z) < 0) continue;
            cells[i + x][j + z]->update_movement();
        }
    }
   
}

/* The Player is special and the map will use the reference to the player to
 * Decide certain things like what to draw. */
void Map::set_player(Entity* p) {
    player = p;
    cells[(int) (p->getX() / 100)][(int) (p->getZ() / 100)]->add_entity(player);
}

/* Add any entity to the map based off the entity's position variables
 * May not be the final function for this purpose but I created it to add a ghost to the map for beta testing */
void Map::add_entity(Entity* p){
    cells[(int)(p->getX() / 100)][(int)(p->getZ() / 100)]->add_entity(p);
}

/* Simple interface for the main loop to have the map keep track of mouse coordinates. */
void Map::update_mouse(int x, int y) {
    mouseX = x;
    mouseY = y;
}

/* Adding a spell is a bit complicated since to setup the details, we need to convert mouse to screen coordinates again. */
int Map::add_spell(Spell* sp, Entity* caster, unsigned long long t) {
    Spell_Details* sd;
    Spell* casted;
    double model[16];
    double proj[16];
    int view[4];
    double ray_origin[3];
    double ray_point[3];
    double ray[3];
    int i;
    double tr;
    // First we check is the spell on cooldown?
    // if (t != 0 && !sp->isCD(t)) return -1; broken for now.
    // We now we have to cast the spell.
    sd = new Spell_Details;
    // We are actually casting the spell. Not creating a dummy version of the spell.
    sd->isRef = false;
    /* This version of ray casting
     * uses a glu call gluUnProject*/
    

    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, view);

    gluUnProject(mouseX, view[3] - mouseY, 0.0,
            model, proj, view,
            ray_origin, ray_origin + 1, ray_origin + 2);

    gluUnProject(mouseX, view[3] - mouseY, 1.0,
            model, proj, view,
            ray_point, ray_point + 1, ray_point + 2);

    for (i = 0; i < 3; i++)
        ray[i] = ray_point[i] - ray_origin[i];
    
    tr = -ray_origin[1] / ray[1];
    
    // Now we set the spell details.
    sd->mouse[0] = ray_origin[0] + ray[0] * tr - player->getX();
    sd->mouse[1] = ray_origin[1] + ray[1] * tr;
    sd->mouse[2] = ray_origin[2] + ray[2] * tr - player->getZ();
    
    // Not implemented yet.
    sd->mouse_release_ptr = NULL;
    
    // Who is casting this magnificent spell?
    sd->player = caster;
    
    // Now that the spell_details is all setup, lets cast.
    casted = sp->cast(sd, t);
    
    // Now we have to register the new cast with the cell.
    cells[(int)(casted->getX() / CELL_SIZE)][(int)(casted->getZ() / CELL_SIZE)]->add_spell(casted);
    
    return 0;
}

/* Adding a spell is a bit complicated since to setup the details, we need to convert mouse to screen coordinates again. */
int Map::add_spell(Spell* sp, Entity* caster, float* dir, unsigned long long t) {
    Spell_Details* sd;
    Spell* casted;
    
    // First we check is the spell on cooldown?
    // if (t != 0 && !sp->isCD(t)) return -1; broken for now.
    // We now we have to cast the spell.
    sd = new Spell_Details;
    // We are actually casting the spell. Not creating a dummy version of the spell.
    sd->isRef = false;
    
    // Now we set the spell details.
    sd->mouse[0] = dir[0];
    sd->mouse[1] = dir[1];
    sd->mouse[2] = dir[2];
    
    // Not implemented yet.
    sd->mouse_release_ptr = NULL;
    
    // Who is casting this magnificent spell?
    sd->player = caster;
    
    // Now that the spell_details is all setup, lets cast.
    casted = sp->cast(sd, t);
    
    // Now we have to register the new cast with the cell.
    cells[(int)(casted->getX() / CELL_SIZE)][(int)(casted->getZ() / CELL_SIZE)]->add_spell(casted);
    return 0;
}

Map* Map::get_current_map(){
    return currmap;
}

int Map::getSizeX(){ return sizeX; }
int Map::getSizeZ(){ return sizeZ; }
/* A function for my example UI 
 * Simply sets the variables to the mouse coordinates. */
void Map::get_mouse(int* x, int* y){
    *x = mouseX;
    *y = mouseY;
}

/* Adds Scenery to their correct cells. */
void Map::add_scenery(Drawable* obj){
    if(obj == NULL) return;
    if(obj->getX() < 0.0) return;
    if(obj->getZ() < 0.0) return;
    cells[(int)(obj->getX() / CELL_SIZE)][(int)(obj->getZ() / CELL_SIZE)]->add_scenery(obj);
}

/* This will essentially be a list of scenery initializions and adding them to the world. */
void Map::populate_world(){
    add_scenery(new LittleGrass(5, 5));
}


//Converts a bmp to rgb
void Map::bmp2rgb(GLubyte img[], int size) {
    int i;
    GLubyte temp;
    
    for (i=0; i<size; i+=3) {
        temp = img[i+2];
        img[i+2] = img[i+1];
        img[i+1] = temp;
        
    }
}



//Creates a texture file inside the argument  img[]
//A reference is available to that texture file by the *ptname
//Use *ptname to bind the texture to your object
void Map::load_bmp(char *fname, GLubyte img[], int size, GLuint *ptname) {
    FILE *fp;
    
    fp = fopen(fname,"rb") ;
    if(fp == NULL) {
        fprintf(stderr,"unable to open texture file %s\n", fname) ;
        exit(1) ;
    }
    
    fseek(fp,8,SEEK_SET) ;
    fread(img,size*size*3,1,fp) ;
    bmp2rgb(img, size*size*3);
    fclose(fp) ;
    
    if (ptname) {
        // initialize the texture
        glGenTextures(1, ptname) ;
        glBindTexture(GL_TEXTURE_2D,*ptname);
        
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT) ;
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT) ;
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR) ;
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR) ;
        
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
                     size,size,
                     0,GL_RGB,GL_UNSIGNED_BYTE,img) ;
    }
}

void Map::init_textures() {
    
    // set pixel storage mode
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    load_bmp("/Users/kyle/Final-Project/illum24_v2.bmp", illum24_v2_img,  smallWidth, &tex_names[ILLUMINATI_FACE_TEX]) ;
}

GLuint Map::get_texture(int index) {
    return tex_names[index];
}

Entity* Map::get_current_player() {
    return player;
}


