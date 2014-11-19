/*
 * HUD.h
 * Author: Nick Habib
 * 11/17/14 @ 1:00 PM
 */

#include "Entity.h"
#include "Map.h"

class HUD {
public:
	HUD(Map* m, Entity* p);
	void draw();
private:
    Map* map;
    Entity* player;
	void drawInfoPlayer();
	void drawMap();
	void drawActionBar();
	void drawLogs();
	void drawTarget();
};
