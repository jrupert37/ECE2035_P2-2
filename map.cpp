//=================================================================
// The map class file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "map.h"
#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items; // Hashtables for all items of the map
    int w, h;         // Map dimensions
    int index;        // Index of map (tells if its the first map or second map)
}; // Map

///////////////////////
//Important Definitions
///////////////////////

#define MHF_NBUCKETS 97     //  Hashing value
#define NUM_MAPS 2         //  You may add more maps here
static Map maps[NUM_MAPS];  //  Array of maps
static int active_map;      //  Current active map on screen


//To erase a MapItem, we can simply replace it 
//with a clear type item called clear sentinel
static const MapItem CLEAR_SENTINEL = { 
    .type = CLEAR,
    .draw = draw_nothing
}; // CLEAR_SENTINEL


/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
     // 1. Return the 1-D XY key
    // Hint: Think about how you accessed location previous projects/hw
    return (X*(maps[active_map].h)) + Y;
} // XY_KEY

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    // Hint: what math operator can be used as an easy way to hash a key?
    // 1. Use MHF_NBUCKETS defined at the top as the value to hash for your hash function
    // 2. Return the hashed key
    return key % MHF_NBUCKETS;
} // map_hash

/**
 * Initializes the map, using a hash_table, setting the width and height.
 */
void maps_init()
{
    // 1. Loop through all possible maps, where for each map's "items", create a hashtable 
    maps[MAIN_MAP].items = createHashTable(map_hash, MHF_NBUCKETS);
    maps[BOSS_MAP].items = createHashTable(map_hash, MHF_NBUCKETS);
    
    // 2. Set width & height for any maps 
    maps[MAIN_MAP].h = 50;
    maps[MAIN_MAP].w = 50;
    maps[BOSS_MAP].h = 20;
    maps[BOSS_MAP].w = 20;

    maps[MAIN_MAP].index = MAIN_MAP;
    maps[BOSS_MAP].index = BOSS_MAP;
    // 3. Set the first map to be active
    set_active_map(MAIN_MAP);
} // maps_init


Map* get_active_map()
{
    // 1. Return a pointer to the current map based on which map is active (active_map)
    //    Hint: What operator do we use for returning addresses?
    //    Note: active_map is set as a Global Variable 
    return &(maps[active_map]);
} // get_active_map

int get_active_map_index()
{
    // 1. Return the index to the current map based on which map is active (active_map)
    return get_active_map()->index;
} // get_active_map_index

Map* set_active_map(int m)
{
    // 1. Set the Global Variable for active map to the map index passed in
    active_map = m;
    // 2. Return a pointer to the current map based on which map is active (active_map)
    return &(maps[active_map]);   
} // set_active_map

/**
 *  Prints out the map for debugging on the terminal
 */

void print_map()
{
    // NOTE: As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'D', 'P', 'A', 'K', 'C', 'N',' ', 'S', 'V', 'M', 'F', 'E', 'B', 'X'};
    Map* map = get_active_map();
    for(int j = 0; j < map->h; j++)
    {
        for (int i = 0; i < map->w; i++)
        {
            MapItem* item = (MapItem*)getItem(map->items, XY_KEY(i, j));
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
} // print_map


/**
 * Returns width of active map
 */
int map_width()
{
    // Hint 1: for this and below functions: use another function to GET the current active map
    // Hint 2: check the struct of a map item
    return get_active_map()->w;
} // map_width

/**
 * Returns height of active map
 */
int map_height()
{
    return get_active_map()->h;
} // map_height

/**
 * Returns the area of the active map
 */
int map_area()
{
    // HINT: You have the width and height to compute area
    Map* currentMap = get_active_map();
    return (currentMap->w * currentMap->h);
} // map_area

/**
 * Returns the MapItem immediately above the given location.
 */
MapItem* get_north(int x, int y)
{
    // 1. Get map item 
    int key = XY_KEY(x, y-1);
    Map* activeMap = get_active_map();
    MapItem* north = (MapItem*) getItem(activeMap->items, key);
    // 2. If the item exist and is a clear type, remove item
    if (north && north->type == CLEAR) {
        north = (MapItem*) removeItem(activeMap->items, key);
    }
    // 3. Return the item 
    return north;
} // get_north

/**
 * Returns the MapItem immediately below the given location.
 */
MapItem* get_south(int x, int y)
{
     // 1. Get map item 
    int key = XY_KEY(x, y+1);
    Map* activeMap = get_active_map();
    MapItem* south = (MapItem*) getItem(activeMap->items, key);
    // 2. If the item exist and is a clear type, remove item
    if (south && south->type == CLEAR) {
        south = (MapItem*) removeItem(activeMap->items, key);
    }
    // 3. Return the item 
    return south;
} // get_south

/**
 * Returns the MapItem immediately right the given location.
 */
MapItem* get_east(int x, int y)
{
    // 1. Get map item 
    int key = XY_KEY(x+1, y);
    Map* activeMap = get_active_map();
    MapItem* east = (MapItem*) getItem(activeMap->items, key);
    // 2. If the item exist and is a clear type, remove item
    if (east && east->type == CLEAR) {
        east = (MapItem*) removeItem(activeMap->items, key);
    }
    // 3. Return the item 
    return east;
} // get_east

/**
 * Returns the MapItem immediately left the given location.
 */
MapItem* get_west(int x, int y)
{
    // 1. Get map item 
    int key = XY_KEY(x-1, y);
    Map* activeMap = get_active_map();
    MapItem* west = (MapItem*) getItem(activeMap->items, key);
    // 2. If the item exist and is a clear type, remove item
    if (west && west->type == CLEAR) {
        west = (MapItem*) removeItem(activeMap->items, key);
    }
    // 3. Return the item 
    return west;
} // get_west

/**
 * Returns the MapItem at current coordinate location
 */
 MapItem* get_here(int x, int y)
 {
    // 1. Get map item 
    int key = XY_KEY(x, y);
    Map* activeMap = get_active_map();
    MapItem* here = (MapItem*) getItem(activeMap->items, key);
    // 2. If the item exist and is a clear type, remove item
    if (here && here->type == CLEAR) {
        here = (MapItem*) removeItem(activeMap->items, key);
    }
    // 3. Return the item 
    return here;
 } // get_here

 
/**
 * Erases item on a location by replacing it with a clear sentinel
 */
void map_erase(int x, int y)
{
    MapItem* item = (MapItem*)insertItem(get_active_map()->items, XY_KEY(x, y), (void*)&CLEAR_SENTINEL);
    if(item){
        free(item);
    }
} // map_erase


//////////////////////////////////////
// Adding specific items to the map //
//////////////////////////////////////
void add_plant(int x, int y)
{
    MapItem* newPlant = (MapItem*) malloc(sizeof(MapItem));
    newPlant->type = PLANT;
    newPlant->draw = draw_plant;
    newPlant->walkable = false;
    newPlant->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newPlant);
    if (val) {
        free(val);
    } // If something is already there, free it
} // add_plant


void add_npc(int x, int y)
{
    // 1. Implement the same way as how we add plant
    //     *Make the NPC NOT walkable
    MapItem* newNPC = (MapItem*)malloc(sizeof(MapItem));
    newNPC->type = NPC;
    newNPC->draw = draw_npc;
    newNPC->walkable = false;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), newNPC);
    if (val) {
        free(val);
    }
} // add_npc


void add_water(int x, int y)
{
    // 1. Implement the same way as how we add plant
    MapItem* newWater = (MapItem*) malloc(sizeof(MapItem));
    newWater->type = WATER;
    newWater->draw = draw_water;
    newWater->walkable = true;
    newWater->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newWater);
    if (val) {
        free(val);
    }
} // add_water

void add_big_tree1(int x, int y) {
    MapItem* newTree = (MapItem*) malloc(sizeof(MapItem));
    newTree->type = BIG_TREE;
    newTree->draw = draw_big_tree1;
    newTree->walkable = true;
    newTree->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newTree);
    if (val) {
        free(val);
    }
}

void add_big_tree2(int x, int y) {
    MapItem* newTree = (MapItem*) malloc(sizeof(MapItem));
    newTree->type = BIG_TREE;
    newTree->draw = draw_big_tree2;
    newTree->walkable = true;
    newTree->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newTree);
    if (val) {
        free(val);
    }
}

void add_big_tree3(int x, int y) {
    MapItem* newTree = (MapItem*) malloc(sizeof(MapItem));
    newTree->type = BIG_TREE;
    newTree->draw = draw_big_tree3;
    newTree->walkable = true;
    newTree->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newTree);
    if (val) {
        free(val);
    }
}

void add_big_tree4(int x, int y) {
    MapItem* newTree = (MapItem*) malloc(sizeof(MapItem));
    newTree->type = BIG_TREE;
    newTree->draw = draw_big_tree4;
    newTree->walkable = true;
    newTree->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newTree);
    if (val) {
        free(val);
    }
}

void add_big_tree(int x, int y)
{
    add_big_tree1(x, y);
    add_big_tree2(x+1, y);
    add_big_tree3(x, y+1);
    add_big_tree4(x+1, y+1);
}

void add_spikes(int x, int y) 
{
    MapItem* newSpikes = (MapItem*) malloc(sizeof(MapItem));
    newSpikes->type = SPIKES;
    newSpikes->draw = draw_spikes;
    newSpikes->walkable = false;
    newSpikes->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newSpikes);
    if (val) {
        free(val);
    }
} // add_spikes

void add_fire(int x, int y, int type)
{
    // 1. Implement the same way as how we add plant
    MapItem* newFire = (MapItem*) malloc(sizeof(MapItem));
    newFire->type = type;
    newFire->draw = draw_fire;
    newFire->walkable = true;
    newFire->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newFire);
    if (val) {
        free(val);
    }
} // add_fire

void add_earth(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* newEarth = (MapItem*) malloc(sizeof(MapItem));
        newEarth->type = EARTH;
        newEarth->draw = draw_earth;
        newEarth->walkable = true;
        newEarth->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, newEarth);
        if (val) free(val); // If something is already there, free it
    }
} // add_earth


void add_buzz(int x, int y)
{
    // 1. Implement the same way as how we add plant
    MapItem* newBuzz = (MapItem*) malloc(sizeof(MapItem));
    newBuzz->type = BUZZ;
    newBuzz->draw = draw_buzz;
    newBuzz->walkable = false;
    newBuzz->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newBuzz);
    if (val) {
        free(val);
    }
} // add_buzz

void add_fire_buzz(int x, int y)
{
    MapItem* newBuzz = (MapItem*) malloc(sizeof(MapItem));
    newBuzz->type = FIRE_BUZZ;
    newBuzz->draw = draw_fire_buzz;
    newBuzz->walkable = false;
    newBuzz->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newBuzz);
    if (val) {
        free(val);
    }
}

void add_slain_buzz(int x, int y)
{
    // 1. Implement the same way as how we add plant
    // Note: This function is to ovewrite Buzz when he is defeated
    //      You can do the following:
    //      -   Overwrite buzz with any other item (say plant, mud)
    //      -   Make a new drawing for a defeated buzz
    //      -   Erase buzz instead 
    MapItem* slainBuzz = (MapItem*) malloc(sizeof(MapItem));
    slainBuzz->type = PLANT;
    slainBuzz->draw = draw_plant;
    slainBuzz->walkable = false;
    slainBuzz->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), slainBuzz);
    if (val) {
        free(val);
    }
    return;
} // add_slain_buzz

void add_chest(int x, int y) 
{
    MapItem* newChest = (MapItem*) malloc(sizeof(MapItem));
    newChest->type = CHEST;
    newChest->draw = draw_chest;
    newChest->walkable = false;
    newChest->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), newChest);
    if (val) {
        free(val);
    }
} // add_chest


////////////////////////////////////
// Adding environment to the map
////////////////////////////////////
void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {   MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
} // add_wall


void add_door(int x, int y, int tm, int tx, int ty, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = DOOR;
        w1->draw = draw_door;
        w1->walkable = false;
        StairsData* data = (StairsData*)malloc(sizeof(StairsData));
        data->tm = tm;
        data->tx = tx;
        data->ty = ty;
        w1->data = data;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
} // add_door

void add_white_block(int x, int y) 
{
    MapItem* newBlock = (MapItem*)malloc(sizeof(MapItem));
    newBlock->type = WHITE_BLOCK;
    newBlock->draw = draw_white_block;
    newBlock->walkable = false;
    newBlock->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), newBlock);
    if (val) {
        free(val);
    }
} // add_white_block


void add_stairs(int x, int y, int tm, int tx, int ty)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = STAIRS;
    w1->draw = draw_stairs;
    w1->walkable = true;
    StairsData* data = (StairsData*) malloc(sizeof(StairsData));
    data->tm = tm;
    data->tx = tx;
    data->ty = ty;
    w1->data = data;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it    
} // add_stairs


void add_cave(int x, int y, int n, int tm, int tx, int ty)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = CAVE;
    if (n==1){
        w1->draw = draw_cave1;
    }
    if (n==2){
        w1->draw = draw_cave2;
    }
    if (n==3){
        w1->draw = draw_cave3;
    }
    if (n==4){
        w1->draw = draw_cave4;
    }
    w1->walkable = false;
    StairsData* data = (StairsData*) malloc(sizeof(StairsData));
    data->tm = tm;
    data->tx = tx;
    data->ty = ty;
    w1->data = data;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it    
} // add_cave


void add_mud(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = MUD;
        w1->draw = draw_mud;
        w1->walkable = true;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
} // add_mud