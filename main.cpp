//=================================================================
// The main program file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


// Projet includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"
#include <math.h>

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

char direction = ' ';
bool Game_Over = false;

// Helper function declarations
void playSound(char* wav);


/////////////////////////
// Struct of Player 
/////////////////////////

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;            // Current locations
    int px, py;         // Previous locations
    bool has_key;       // flag when obtained the key
    bool game_solved;   // flag when game is complete
    bool talked_to_npc; // flag when you've talked to npc
    bool ramblin;
    bool is_hidden;
    int num_lives;
    //You may add more flags as needed
} Player;



/////////////////////////
// Get Action
/////////////////////////

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 * Get Actions from User (pushbuttons, and nav_switch)
 * Based on push button and navigation switch inputs, determine which action
 * needs to be performed (may be no action).
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define RAMBLIN 7

int get_action(GameInputs inputs)
{
    // 1. Check your action and menu button inputs and return the corresponding action value
    // b1 = action button
    // b2 = menu button
    if (!inputs.b1) {
        return ACTION_BUTTON;
    } else if (!inputs.b2) {
        return RAMBLIN;
    } else if (inputs.ns_left) {
        return GO_LEFT;
    } else if (inputs.ns_right) {
        return GO_RIGHT;
    } else if (inputs.ns_up) {
        return GO_UP;
    } else if (inputs.ns_down) {
        return GO_DOWN;
    }
    // 2. Check for your navigation switch inputs and return the corresponding action value
    
    // If no button is pressed, just return no action value
    return NO_ACTION;
}




/////////////////////////
// Helper Functions:
/////////////////////////
// Feel free to define any helper functions here for update game





/////////////////////////
// Update Game
/////////////////////////

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define WIN       3
#define FULL_DRAW 2
#define LOSE      4

int update_game(int action)
{
    
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    MapItem* item = NULL;
    MapItem* n = NULL;
    MapItem* e = NULL;
    MapItem* s = NULL;
    MapItem* w = NULL;
    MapItem* here = NULL;
    n = get_north(Player.x, Player.y);
    e = get_east(Player.x, Player.y);
    s = get_south(Player.x, Player.y);
    w = get_west(Player.x, Player.y);
    here = get_here(Player.x, Player.y);


    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {
        case GO_UP:
            //1. Check the item north of the player
           // draw_text("            ", 0, 0, BLACK);
            item = get_north(Player.x, Player.y);
            //2. Make sure to not walk through walls
            // If it is not a wall (or player is in ramblin mode), walk up by updating player's coordinates
            if (Player.ramblin || item->walkable) {
                Player.x = Player.x;
                Player.y = Player.y - 1;
            }
            if (item->type == SPIKES) {
                speech("You have run", "into spikes!");
                speech("You lose a", "heart!");
                Player.num_lives--;
                draw_hearts(0, 120, Player.num_lives);
                if (Player.num_lives == 0) {
                    return LOSE;
                }
            }
            item = get_here(Player.x, Player.y);
            if (item->type == BIG_TREE) {
                Player.is_hidden = true;
            } else
            {
                Player.is_hidden = false;
            }
            direction = 'N';    // set current direction to N (north)
            return FULL_DRAW;
            break;
            
        case GO_LEFT:
            item = get_west(Player.x, Player. y);
            if (Player.ramblin || item->walkable) {
                Player.x = Player.x - 1;
                Player.y = Player.y;
            }   
            if (item->type == SPIKES) {
                speech("You have run", "into spikes!");
                speech("You lose a", "heart!");
                Player.num_lives--;
                draw_hearts(0, 120, Player.num_lives);
                if (Player.num_lives == 0) {
                    return LOSE;
                }
            }
            item = get_here(Player.x, Player.y);
            if (item->type == BIG_TREE) {
                Player.is_hidden = true;
            } else
            {
                Player.is_hidden = false;
            }
            direction = 'W';    // set current direction to W (west)
            return FULL_DRAW;
            break;
            
        case GO_DOWN:
            item = get_south(Player.x, Player.y);
            if (Player.ramblin || item->walkable){
                Player.x = Player.x;
                Player.y = Player.y + 1;
            }
            if (item->type == SPIKES) {
                speech("You have run", "into spikes!");
                speech("You lose a", "heart!");
                Player.num_lives--;
                draw_hearts(0, 120, Player.num_lives);
                if (Player.num_lives == 0) {
                    return LOSE;
                }
            }
            item = get_here(Player.x, Player.y);
            if (item->type == BIG_TREE) {
                Player.is_hidden = true;
            } else
            {
                Player.is_hidden = false;
            }
            direction = 'S';    // set current direction to S (south)
            return FULL_DRAW;
            break;
            
        case GO_RIGHT:
            item = get_east(Player.x, Player.y);
            if (Player.ramblin || item->walkable) {
                Player.x = Player.x + 1;
                Player.y = Player.y;
            }
            if (item->type == SPIKES) {
                speech("You have run", "into spikes!");
                speech("You lose a", "heart!");
                Player.num_lives--;
                draw_hearts(0, 120, Player.num_lives);
                if (Player.num_lives == 0) {
                    return LOSE;
                }
            }
            item = get_here(Player.x, Player.y);
            if (item->type == BIG_TREE) {
                Player.is_hidden = true;
            } else
            {
                Player.is_hidden = false;
            }
            direction = 'E';    // set current directino to E (east)
            return FULL_DRAW;
            break;
            
        case ACTION_BUTTON:

            // 1. Check if near NPC, 
            //     - if so, mark the player has talked and give instructions on what to do
            //     - if the game is solved (defeated Buzz), give the player the key
            //     - return FULL_DRAW to redraw the scene
            if (n->type == NPC || e->type == NPC || s->type == NPC || w->type == NPC) {
                // If player has not yet talked to NPC
                if(Player.talked_to_npc == false && Player.game_solved == false) {
                    Player.talked_to_npc = true;
                    speech("Find cave in the", "South-West corner");
                    speech("Enter the cave", "and defeat Buzz!");
                    speech("He has a weakness", "for fire...");
                    speech("If you succeed", "in defeating him");
                    speech("I will give", "you a key!");
                    speech("By the way...", "");
                    speech("You can regain", "lost health");
                    speech("By finding one", "of the");
                    speech("nearby campsites.","");
                    speech("Follow one of", "the earthen");
                    speech("paths toward", "the north");
                    speech("and while", "standing next");
                    speech("to one of the", "fires...");
                    speech("press the action", "button!");
                    return FULL_DRAW;
                }
                // If player has talked to NPC but has not yet defeated buzz
                else if (Player.talked_to_npc == true && Player.game_solved == false) {
                    speech("Have you found", "the cave?");
                    speech("Check the SW", "corner!");
                    speech("If you defeat", "Buzz...");
                    speech("I will give", "you a key!");
                    speech("He has a weakness", "for fire...");
                    speech("And by the way...", "");
                    speech("You can regain", "lost health");
                    speech("By finding one", "of the");
                    speech("nearby campsites.","");
                    speech("Follow one of", "the earthen");
                    speech("paths toward", "the north");
                    speech("and while", "standing next");
                    speech("to one of the", "fires...");
                    speech("press the action", "button!");
                    return FULL_DRAW;
                }
                // If player has defeated buzz and not yet gotten the key
                else if (Player.game_solved == true && Player.has_key == false) {
                    speech("Well done!", "Here is your key!");
                    speech("Unlock the door", "to the East.");
                    speech("You may find", "a prize...");
                    Player.has_key = true;
                    return FULL_DRAW;
                }
                // If player has defeated buzz and already gotten the key
                else {
                    speech("Well done", "defeating Buzz!");
                    speech("Use your key to", "unlock the door");
                    speech("And collect your", "prize!");
                    return FULL_DRAW;
                }
            // If the palyer is attempting to enter a cave
            } else if (n->type == CAVE || e->type == CAVE || s->type == CAVE || w->type == CAVE) {
                if (Player.talked_to_npc) {
                    // If the player has not yet defeated buzz, give instructions
                    if (!Player.game_solved) {
                        speech("You are entering", "Buzz's cave!");
                        speech("Defeat him by", "casting spells.");
                        speech("Use the action", "button near a");
                        speech("spell location", "to cast!");
                    }
                    // Update player coordinates to initial position inside the boss map
                    Player.x = 17;
                    Player.y = 9;
                    set_active_map(BOSS_MAP);
                // If player has not yet talked to NPC, tell player to talk to them first before entering
                } else {
                    speech("You must talk", "to NPC first...");
                }
                return FULL_DRAW;
            // If the player is attempting to enter through a door
            } else if (n->type == DOOR || e->type == DOOR || s->type == DOOR || w->type == DOOR) {
               // If the player has gained the key from the NPC
               if (Player.has_key) {
                    // Erase the door
                    map_erase(45, 24);
                    speech("Congratulations!", "");
                    speech("Open the chest to", "get your prize!");
                    return FULL_DRAW;
                // If the player does not have the key
                } else {
                    // If the player has not yet talked to NPC, prompt player to talk to them first
                    if (!Player.talked_to_npc) {
                        speech("You must talk", "to NPC first...");
                    // If player has talked to NPC but not yet gotten the key
                    } else {
                        speech("Key required", "to open door...");
                    }
                }
            // If the player is attempting to use stairs
            } else if (n->type == STAIRS || e->type == STAIRS || s->type == STAIRS || w->type == STAIRS || here->type == STAIRS) {
                // Update player coordinates to position next to cave entrance in the main map
                Player.x = 2;
                Player.y = 46;
                set_active_map(MAIN_MAP);
                return FULL_DRAW;
            } else if (n->type == FIRE_HEALTH || e->type == FIRE_HEALTH || s->type == FIRE_HEALTH || w->type == FIRE_HEALTH) { 
                if (Player.num_lives < 3) {
                    speech("You have gained", "a heart back!");
                    Player.num_lives++;
                    draw_hearts(0, 120, Player.num_lives);
                } else {
                    speech("You have full", "health already!");
                }
                return FULL_DRAW;
            } else if (get_active_map_index() == BOSS_MAP) {
                // If player is in the boss map, and adjacent to fire/water/earth elements
                if ((here->type == FIRE || n->type == FIRE || e->type == FIRE || s->type == FIRE || w->type == FIRE) && !Player.game_solved) {
                    // Fire is Buzz's weakness! Replace buzz with slain_buzz (tree), prompt player to return to NPC
                    speech("You have cast", "Fire!");
                    speech("Buzz has been", "defeated!");
                    speech("Go back and", "talk to NPC.");
                    map_erase(3, 9);
                    add_slain_buzz(3, 9);
                    Player.game_solved = true;  // Player has successfully defeated Buzz
                    return FULL_DRAW;
                // Other elements do not defeat buzz...
                } else if ((here->type == WATER || n->type == WATER || e->type == WATER || s->type == WATER || w->type == WATER) && !Player.game_solved) {
                    speech("You have cast", "Water!");
                    speech("But Buzz remains", "undefeated!");
                    enemy_turn();
                    if (Player.num_lives == 0) {
                        return LOSE;
                    }
                    speech("Try casting", "again!");
                    return FULL_DRAW;
                } else if ((here->type == EARTH || n->type == EARTH || e->type == EARTH || s->type == EARTH || w->type == EARTH) && !Player.game_solved) {
                    speech("You have cast", "Earth!");
                    speech("But Buzz remains", "undefeated!");
                    enemy_turn();
                    if (Player.num_lives == 0) {
                        return LOSE;
                    }
                    speech("Try casting", "again!");
                    return FULL_DRAW;
                }
            // If the player is approaching the chest
            } else if (n->type == CHEST || e->type == CHEST || s->type == CHEST || w->type == CHEST || here->type == CHEST) {
                if (Player.game_solved) {
                    speech("You have earned", "1000 Rupees!");
                    speech("Congratulations!", "");
                    return WIN;
                } else {
                    // If player walked through door or wall in ramblin mode
                    speech("Nice try! You", "must defeat buzz");
                    speech("before you can", "claim your prize!");
                    return FULL_DRAW;
                }
            }
            // Feel free to add more functions as you make the game!
            break;

        case RAMBLIN:
            Player.ramblin = !Player.ramblin;
            wait(0.03);
            break;
    }
    
    return NO_RESULT;
}


void enemy_turn() {
    speech("Now it is", "Buzz's turn!");
    speech("He has cast an", "anti-hero spell!");
    speech("You lose a", "heart!");
    Player.num_lives--;
    draw_hearts(0, 120, Player.num_lives);
}

bool key_drawn = false;
/////////////////////////
// Draw Game
/////////////////////////

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();

    // If player has defeated buzz, received the key, and opened the chest
    if(init == WIN) {
        Game_Over = true;
        // Clear the uLCD screen
        uLCD.cls(); 
        // And display game over text
        draw_text("Game Over", 8, 5, GREEN);
        draw_text("You Win!", 9, 6, GREEN);
        return;
    } else if (init == LOSE) {
        Game_Over = true;
        uLCD.cls();
        draw_text("Game Over", 8, 5, RED);
        draw_text("You Lose!", 9, 5, RED);
        return;
    }
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
//            if (init && i == 0 && j == 0) // Only draw the player on init
            if (!Player.is_hidden && i == 0 && j == 0) // always draw the player
            {
                draw_player(u, v, Player.has_key);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
                else if (curr_item && curr_item->type == CLEAR)
                {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars    
    draw_upper_status();
    draw_lower_status();

    // Create lines of text displaying the characters x,y coordinates and current direciton (N,E,S, or W)
    char xCoordinate[9];
    char yCoordinate[9];
    sprintf(xCoordinate, "(%d,", Player.x);
    sprintf(yCoordinate, "%d) %c    ", Player.y, direction);
    strcat(xCoordinate, yCoordinate);
    // Display this text at the top of the screen
    draw_text(xCoordinate, 0, 0, WHITE);

    if (Player.has_key && !key_drawn) {     // key only needs to be drawn once
        draw_key(115, 0);
        key_drawn = true;
    }

   // draw_hearts(0, 120, Player.num_lives);
}



/////////////////////////
// Map Intialization
/////////////////////////

// Important locations for all maps
int cb_loc[2] = {5,20}; //Location of the center of the cave


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    //Initialize and sets current map to the first map
    set_active_map(MAIN_MAP);

    /////////////////////////
    //Initial Environmnet
    /////////////////////////

    //Adding wall borders 
    add_wall(0,              0,              HORIZONTAL, 50);
    add_wall(0,              49,             HORIZONTAL, 50);
    add_wall(0,              0,              VERTICAL,   50);
    add_wall(49,             0,              VERTICAL,   50);
    

    // Add extra wall elements
    // Add wall elements in far NE corner
    add_wall(44, 1, HORIZONTAL, 5);
    add_wall(48, 2, VERTICAL, 4);

    //Add earth/stone paths
    add_earth(28, 10, VERTICAL, 2);
    add_earth(26, 11, HORIZONTAL, 2);
    add_earth(26, 12, VERTICAL, 3);
    add_earth(22, 14, HORIZONTAL, 4);
    add_earth(20, 15, HORIZONTAL, 3);
    add_earth(20, 16, VERTICAL, 4);
    add_earth(21, 19, VERTICAL, 2);
    add_earth(22, 20, HORIZONTAL, 3);
    add_earth(24, 21, VERTICAL, 3);

    add_earth(45, 2, VERTICAL, 3);
    add_earth(46, 2, VERTICAL, 3);
    add_earth(47, 3, VERTICAL, 2);
    add_earth(44, 4, VERTICAL, 2);
    add_earth(43, 5, VERTICAL, 9);
    add_earth(42, 13, VERTICAL, 6);
    add_earth(40, 18, HORIZONTAL, 2);
    add_earth(40, 19, VERTICAL, 2);
    add_earth(37, 20, HORIZONTAL, 3);
    add_earth(37, 21, VERTICAL, 3);


    add_earth(7, 24, HORIZONTAL, 38);


    // // Add fire elements to "campsites"
    add_fire(47, 2, FIRE_HEALTH);
    add_fire(28, 9, FIRE_HEALTH);
    add_fire(6, 22, FIRE);
    add_fire(6, 26, FIRE);
    

    //Add water/ponds
    add_water(12, 7);
    add_water(13, 6);
    add_water(13, 8);
    add_water(14, 7);
    
    add_water(27, 5);
    add_water(28, 4);
    add_water(28, 5);
    add_water(28, 6);
    add_water(29, 5);

    add_water(39, 10);
    add_water(40, 10);


    add_water(27, 42);
    add_water(28, 42);
    add_water(27, 43);
    add_water(28, 43);

    
    // Add mud elements around water
    add_mud(13, 5, HORIZONTAL, 1);
    add_mud(11, 7, HORIZONTAL, 1);
    add_mud(15, 7, HORIZONTAL, 1);
    add_mud(13, 9, HORIZONTAL, 1);

    add_mud(27, 3, HORIZONTAL, 3);
    add_mud(26, 4, VERTICAL, 3);
    add_mud(27, 7, HORIZONTAL, 3);
    add_mud(30, 4, VERTICAL, 3);

    add_mud(39, 9, HORIZONTAL, 2);
    add_mud(39, 11, HORIZONTAL, 2);

    add_mud(26, 41, HORIZONTAL, 1);
    add_mud(26, 44, HORIZONTAL, 1);
    add_mud(29, 41, HORIZONTAL, 1);
    add_mud(29, 44, HORIZONTAL, 1);


    // Add plants/trees
    add_plant(2, 2);
    add_plant(39, 2);
    add_plant(9, 3);
    add_plant(25, 3);
    add_plant(31, 3);
    add_plant(18, 5);
    add_plant(37, 6);
    add_plant(13, 7);
    add_plant(23, 7);
    add_plant(30, 8);
    add_plant(46, 8);
    add_plant(7, 9);
    add_plant(19, 10);
    add_plant(38, 10);
    add_plant(41, 10);
    add_plant(2, 12);
    add_plant(14, 12);
    add_plant(34, 12);
    add_plant(45, 14);
    add_plant(28, 16);
    add_plant(39, 16);
    add_plant(11, 17);
    add_plant(4, 21);
    add_plant(3, 22);
    add_plant(3, 23);
    add_plant(3, 24);
    add_plant(3, 25);
    add_plant(3, 26);
    add_plant(4, 27);
    add_plant(41, 23);
    add_plant(41, 25);
    add_plant(34, 26);
    add_plant(6, 47);
    add_plant(7, 47);
    add_plant(6, 45);
    add_plant(7, 45);
    add_plant(8, 45);
    add_plant(33, 46);
    add_plant(43, 46);
    add_plant(25, 45);
    add_plant(30, 45);
    add_plant(15, 43);
    add_plant(40, 43);
    add_plant(46, 43);
    add_plant(22, 41);
    add_plant(1, 40);
    add_plant(25, 40);
    add_plant(30, 40);
    add_plant(44, 40);
    add_plant(35, 38);
    add_plant(21, 35);
    add_plant(29, 35);
    add_plant(44, 35);
    add_plant(3, 34);
    add_plant(12, 31);
    add_plant(21, 31);
    add_plant(34, 31);
    add_plant(25, 28);
    add_plant(8, 47);

    add_big_tree(14, 36);
    add_big_tree(17, 20);

    add_spikes(8, 36);
    add_spikes(5, 16);
    add_spikes(42, 30);
    add_spikes(21, 46);

    // Add entrance to Buzz's cave
    add_earth(1, 44, HORIZONTAL, 1);
    add_cave(1, 46, 3, BOSS_MAP, 17, 9);
    add_earth(1, 48, HORIZONTAL, 1);

    
    /////////////////////////////////
    // Characters and Items for the map
    /////////////////////////////////

    // Add NPC
    add_npc(5, 24);  //NPC is initialized to (x,y) = 5, 24.

    add_wall(45, 22, HORIZONTAL, 4);
    add_wall(45, 23, HORIZONTAL, 1);
    add_wall(45, 25, HORIZONTAL, 1);
    add_wall(45, 26, HORIZONTAL, 4);

    // Add door and chest on East wall
    add_chest(48, 24);
    add_door(45, 24, 0, 0 , 0, VERTICAL, 1);
}


void init_boss_map()
{
     //Sets current map to the boss map
    Map* cm=set_active_map(BOSS_MAP);

    // 1. Add walls to the smaller map.
    //    Set the dimensions to be 16x16  <-- you may change to your liking, but must be smaller than the main map
    //    Hint: See how walls are initialized in the main map
    add_wall(0,              0,              HORIZONTAL, 20);
    add_wall(0,              19,             HORIZONTAL, 20);
    add_wall(0,              0,              VERTICAL,   20);
    add_wall(19,             0,              VERTICAL,   20);
        
    // Add extra wall/plant elements
    add_wall(1, 7, VERTICAL, 5);

    add_plant(18, 7);
    add_plant(18, 11);
    
    // 2. Add your three spells at different locations
    add_fire(6, 6, FIRE);
    add_water(6, 9);
    add_earth(6, 12, HORIZONTAL, 1);
    
    // 3. Add Evil Buzz
    add_buzz(3, 9);

    // You may add any extra characters/items here for your project

    add_mud(9, 9, HORIZONTAL, 10);
    
    // Add stairs back to main map
    add_stairs(18, 9, MAIN_MAP, 4, 46);
}


/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");


    //uLCD.filled_rectangle(64, 64, 74, 74, RED); //DELETE OR COMMENT THIS LINE  <-- It is a temporary indicator that your LCD is working before you implement your code
    
    // Initialize the maps
    maps_init();
    init_main_map();
    init_boss_map();
    set_active_map(MAIN_MAP);
    // Set player initial conditions
    Player.x = Player.y = 6;
    Player.has_key = false;
    Player.game_solved = false;
    Player.talked_to_npc = false;
    Player.ramblin = false;
    Player.is_hidden = false;
    Player.num_lives = 3;
    draw_game(true);
    draw_hearts(0, 120, Player.num_lives);
    
    // Main game loop
    // Run while Game_Over is false (player has not solved the quest and opened the chest)
    while(!Game_Over)
    {

        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actually do the game update:
        // 1. Read inputs        
        // 2. Determine action (get_action)       
        int action = get_action(read_inputs());
        // 3. Update game (update_game)
        int result = update_game(action);  // Set this variable "result" for the resulting state after update game     
        draw_game(result);

        // 4. Draw screen to uLCD
        //bool full_draw = false;
        //if (result == FULL_DRAW) full_draw = true;
        //draw_game(full_draw);
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
   
}




/////////////////////////////
//Advanced Features
/////////////////////////////

// Plays a wavfile
void playSound(char* wav)
{
    //open wav file
    FILE *wave_file;
    wave_file=fopen(wav,"r");
    
    if(wave_file != NULL) 
    {
        printf("File opened successfully\n");

        //play wav file
        printf("Sound playing...\n");
        waver.play(wave_file);
    
        //close wav file
        printf("Sound stopped...\n");
        fclose(wave_file);
        return;
    }
    
    printf("Could not open file for reading - %s\n", wav);
    return;
}
