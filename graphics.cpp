// ============================================
// The graphics class file
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "graphics.h"
#include "globals.h"



///////////////////////////////////////////
// Drawing Images based on Characters
///////////////////////////////////////////

//Additional color definitions
#define YELLOW 0xFFFF00         // Y
#define BROWN  0xD2691E         
#define DIRT   BROWN            // B
#define TEAL   0x0AE5F5         // T
#define AZURE  0x007FFF         // A
#define C_DBROWN    0x643C04    // 1    // chest_darkBrown
#define C_LBROWN    0xC07707    // 2    // chest_lightBrown
#define LPURPLE     0x6969E2    // 4
#define NPC_DGRAY   0xA3A1A1    // 6
#define NPC_LGRAY   0xD4D0D0    // 7
#define NPC_PURPLE  0x976EEC    // 8
#define NPC_BROWN   0x9F5F16    // 9
#define SKIN        0xFFC384    // S
#define LK_GREEN    0x09D809    // E
#define LK_ORANGE   0xE55110    // O
#define FR_ORANGE   0xF49806    // F
#define WT_LBLUE    0x00FFFF    // B
#define WT_DBLUE    0x0000FF    // L


// You can define more hex colors here


//Function to draw images based on characters
// - The function takes an image array and changes the color 
//   labeled by a character to a hex value (ex: 'Y' -> 0xFFF00)
void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        //You can add more characters by defining their hex values above
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'A') colors[i] = AZURE;
        else if (img[i] == 'T') colors[i] = TEAL;
        else if (img[i] == '1') colors[i] = C_DBROWN;
        else if (img[i] == '2') colors[i] = C_LBROWN;
        else if (img[i] == 'W') colors[i] = WHITE;
        else if (img[i] == '4') colors[i] = LPURPLE;
        else if (img[i] == '6') colors[i] = NPC_DGRAY;
        else if (img[i] == '7') colors[i] = NPC_LGRAY;
        else if (img[i] == '8') colors[i] = NPC_PURPLE;
        else if (img[i] == '9') colors[i] = NPC_BROWN;
        else if (img[i] == 'S') colors[i] = SKIN;
        else if (img[i] == 'E') colors[i] = LK_GREEN;
        else if (img[i] == 'S') colors[i] = SKIN;
        else if (img[i] == 'O') colors[i] = LK_ORANGE;
        else if (img[i] == 'F') colors[i] = FR_ORANGE;
        else if (img[i] == 'B') colors[i] = WT_DBLUE;
        else if (img[i] == 'L') colors[i] = WT_LBLUE;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}


///////////////////////////////////////////
//Simple drawing of objects using uLCD methods
///////////////////////////////////////////

void draw_nothing(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_player(int u, int v, int key)
{
    const char* img;
    if (!key)
    {
        img =
            "   EEEEE   "
            "S EOOOOOE S"
            "SSOSESESOSS"
            " SSSOSOSSS "
            " OSSSSSSSO "
            " OESSOSSEO "
            "  SEEEEES  "
            " SSEOOOESS "
            " SOOOEOOOS "
            " SEEOOOEES "
            "   EEEEE   ";
    }
    else
    {
         img =
            "   EEEEE   "
            "S EOOOOOE S"
            "SSOSESESOSS"
            " SSSOSOSSS "
            " OSSSSSSSO "
            "YYYYYOYSYO "
            "YYYYYEYEY  "
            "YYOOYOYEYS "
            "YYOOYYYEYS "
            "YYYYYYYYYS "
            "YYYYYEEE   ";
    }
    draw_img(u, v, img);
}


void draw_wall(int u, int v)
{
    const char* img = 
        "AAAAAAAAAAA"
        "ATTTATTTATA"
        "AAAAAAAAAAA"
        "ATATTTATTTA"
        "AAAAAAAAAAA"
        "ATTTATTTATA"
        "AAAAAAAAAAA"
        "ATATTTATTTA"
        "AAAAAAAAAAA"
        "ATTTATTTATA"
        "AAAAAAAAAAA";
    draw_img(u, v, img);
    //uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_key(int u, int v)
{
    const char* img =
        "          "
        " YY   Y  Y"
        "YYYY  Y  Y"
        "Y  YYYYYYY"
        "Y  YYYYYYY"
        "YYYY      "
        " YY       "
        "          ";
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        //You can add more characters by defining their hex values above
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'A') colors[i] = AZURE;
        else if (img[i] == 'T') colors[i] = TEAL;
        else if (img[i] == '1') colors[i] = C_DBROWN;
        else if (img[i] == '2') colors[i] = C_LBROWN;
        else if (img[i] == 'W') colors[i] = WHITE;
        else if (img[i] == '4') colors[i] = LPURPLE;
        else if (img[i] == '6') colors[i] = NPC_DGRAY;
        else if (img[i] == '7') colors[i] = NPC_LGRAY;
        else if (img[i] == '8') colors[i] = NPC_PURPLE;
        else if (img[i] == '9') colors[i] = NPC_BROWN;
        else if (img[i] == 'S') colors[i] = SKIN;
        else if (img[i] == 'E') colors[i] = LK_GREEN;
        else if (img[i] == 'S') colors[i] = SKIN;
        else if (img[i] == 'O') colors[i] = LK_ORANGE;
        else if (img[i] == 'F') colors[i] = FR_ORANGE;
        else if (img[i] == 'B') colors[i] = WT_DBLUE;
        else if (img[i] == 'L') colors[i] = WT_LBLUE;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 10, 8, colors);
    wait_us(250); // Recovery time!
}

void draw_hearts(int u, int v, int num_lives) 
{
    const char* img = 
        "  R   R  "
        " RRR RRR "
        " RRRRRRR "
        " RRRRRRR "
        "  RRRRR  "
        "   RRR   "
        "    R    ";
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        //You can add more characters by defining their hex values above
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'A') colors[i] = AZURE;
        else if (img[i] == 'T') colors[i] = TEAL;
        else if (img[i] == '1') colors[i] = C_DBROWN;
        else if (img[i] == '2') colors[i] = C_LBROWN;
        else if (img[i] == 'W') colors[i] = WHITE;
        else if (img[i] == '4') colors[i] = LPURPLE;
        else if (img[i] == '6') colors[i] = NPC_DGRAY;
        else if (img[i] == '7') colors[i] = NPC_LGRAY;
        else if (img[i] == '8') colors[i] = NPC_PURPLE;
        else if (img[i] == '9') colors[i] = NPC_BROWN;
        else if (img[i] == 'S') colors[i] = SKIN;
        else if (img[i] == 'E') colors[i] = LK_GREEN;
        else if (img[i] == 'S') colors[i] = SKIN;
        else if (img[i] == 'O') colors[i] = LK_ORANGE;
        else if (img[i] == 'F') colors[i] = FR_ORANGE;
        else if (img[i] == 'B') colors[i] = WT_DBLUE;
        else if (img[i] == 'L') colors[i] = WT_LBLUE;
        else colors[i] = BLACK;
    }
    int offset = 0;
    int j;
    for (j = 0; j < num_lives; j++) {
        uLCD.BLIT(u+offset, v, 9, 7, colors);
        offset += 9;
    }
    int all_black[189];
    for (j = 0; j < 189; j++) {
        all_black[j] = BLACK;
    }
    uLCD.BLIT(offset, v, 27, 7, all_black);
}

void draw_door(int u, int v) // x, y
{
    const char* img = 
        "     Y     "
        "     Y     "
        "     Y     "
        "     Y     "
        "     Y     "
        "     Y     "
        "     Y     "
        "     Y     "
        "     Y     "
        "     Y     "
        "     Y     ";
    draw_img(u, v, img);
    // draw_nothing(u,v);
    // uLCD.line(u, v+6, u+11, v+6, 0xFFFF00);
}

void draw_white_block(int u, int v)
{
    const char* img =
        "WWWWWWWWWWW"
        "WWWWWWWWWWW"
        "WWWWWWWWWWW"
        "WWWWWWWWWWW"
        "WWWWWWWWWWW"
        "WWWWWWWWWWW"
        "WWWWWWWWWWW"
        "WWWWWWWWWWW"
        "WWWWWWWWWWW"
        "WWWWWWWWWWW"
        "WWWWWWWWWWW";
    draw_img(u, v, img);
}

/**
 * Draw the upper status bar.
 */
void draw_upper_status()
{
    uLCD.line(0, 9, 127, 9, GREEN);
}

/**
 * Draw the lower status bar.
 */ 
void draw_lower_status()
{
    uLCD.line(0, 118, 127, 118, GREEN);
}

/**
 * Draw the border for the map.
 */
void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

///////////////////////////////////////////
//Sprite drawing of objects using draw_img function
///////////////////////////////////////////

void draw_plant(int u, int v)
{
    const char* img = 
        "           "
        " GGGGGGGG  "
        " GGGGGGGGG "
        "GGGGGGGGGGG"
        "GGGGGGGGGGG"
        " GGGGGGGG  "
        "    DD     "
        "    DD     "
        "    DD     "
        "   DDDDD   "
        "  D  D  D  ";
    draw_img(u, v, img);
}

void draw_big_tree1(int u, int v) 
{
    const char* img =
        "        GGG"
        "    GGGGGGW"
        "   GGWWGWWG"
        "   GGGWGGGG"
        "  GWWGGWGWG"
        "  GGGGGGGGG"
        " GGGGWWGGWG"
        "GGGGGGGWGGG"
        "GGGGGGGGGGG"
        "GGGGGGGGGGG"
        " GGGGGGGGGG";
    draw_img(u, v, img);
}

void draw_big_tree2(int u, int v)
{
    const char* img = 
        "GG         "
        "WGGGGGGGG  "
        "GGWWGWWGGG "
        "WGGWGGWWGGG"
        "GGGWGGGGGGG"
        "GWGWGWGGWGG"
        "GGGGGGGGGGW"
        "GGGGGGGGGGW"
        "GGGGGGGGGGG"
        "WGDDGGGGGGW"
        "WWDDGGGGGGW";
    draw_img(u, v, img);
}

void draw_big_tree3(int u, int v)
{
    const char* img =
        "  GGGGGGDGG"
        "   GGGGGDGD"
        "     GWGDDD"
        "      DDDDD"
        "       DDDD"
        "        DDD"
        "        DDD"
        "       DDDD"
        "       DDDD"
        "      DDDDD"
        "    DDDDDDD";
    draw_img(u, v, img);
}

void draw_big_tree4(int u, int v) 
{
    const char* img = 
        "WWDDDGGGGG "
        "WDDD GGGG  "
        "DDDD   G   "
        "DDDDD      "
        "DDDDD      "
        "DDDDD      "
        "DDDD       "
        "DDDD       "
        "DDDDD      "
        "DDDDDD     "
        "DDDDDDD    ";
    draw_img(u, v, img);
}

void draw_spikes(int u, int v) 
{
    const char* img =
        "           "
        " R   R   R "
        " R   R   R "
        " RR  RR  RR"
        " RR  RR  RR"
        "RRR RRR RRR"
        "RW5 RW5 RW5"
        "WW5 WW5 WW5"
        "WW5 WW5 WW5"
        "WW5WWW5WWW5"
        "WW5WWW5WWW5";
    draw_img(u, v, img);
}

void draw_npc(int u, int v)
{
    const char* img = 
        "    666    "
        "   6SSS6   "
        "  6S S S6  "
        "  6SS6SS6  "
        "996S6S6S6  "
        " 98666668S "
        "S9S966689SS"
        "S9S896698SS"
        " 98889988  "
        " 97888887  "
        " 9 78887   ";
    draw_img(u, v, img);
}

void draw_stairs(int u, int v)
{
    const char* img =
        "        333"
        "        353"
        "      33333"
        "      35553"
        "    3333333"
        "    3555553"
        "  333333333"
        "  355555553"
        "33333333333"
        "35555555553"
        "33333333333";
    draw_img(u, v, img);
}



////////////////////////////////////////////
//Examples of Piskel sprite C array export
////////////////////////////////////////////

void draw_buzz(int u, int v)
{

int new_piskel_data[121] = {
0x00000000, 0x00000000, 0x00000000, 0xff58110c, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff58110c, 0x00000000, 0x00000000, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffffff, 0xff0000ff, 0xff606060, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff0000ff, 0xffffffff, 0xff0000ff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 
0x00000000, 0xffffff00, 0xffffff00, 0xffffff00, 0xff0000ff, 0xff0000ff, 0xff606060, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0x00000000, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff58110c, 0xff58110c, 0xff137bff, 0xffffffff, 0x00000000, 0x00000000, 
0xff137bff, 0x00000000, 0xff137bff, 0xff58110c, 0xff58110c, 0xff58110c, 0xffffff00, 0xff58110c, 0xff137bff, 0x00000000, 0x00000000, 
0x00000000, 0xff137bff, 0xff137bff, 0x00000000, 0x00000000, 0xffffff00, 0xff137bff, 0xff137bff, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff58110c, 0xff58110c, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff58110c, 0xffffff00, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}


void draw_water(int u, int v)
{


int new_piskel_data[121] = {

0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0x00000000, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0x00000000, 0x00000000, 0x00000000

};    
   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}

void draw_fire(int u, int v)
{

int new_piskel_data[121] = {

0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0xffff0009, 0xffff0009, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0xffff0009, 0xffff0009, 0xffff0009, 0xffff0009, 0x00000000, 0xffff0009, 0xffff0009, 0xffff0009, 0x00000000, 0x00000000, 0x00000000, 
0xffff0009, 0xffff0009, 0xffdeb200, 0xffff0009, 0x00000000, 0xffff0009, 0xffdeb200, 0xffff0009, 0xffff0009, 0x00000000, 0x00000000, 
0x00000000, 0xffff0009, 0xffdeb200, 0xffdeb200, 0xffff0009, 0xffdeb200, 0xffdeb200, 0xffff0009, 0xffff0009, 0x00000000, 0x00000000, 
0x00000000, 0xffff0009, 0xffdeb200, 0xffdeb200, 0xffdeb200, 0xffdeb200, 0xffdeb200, 0xffff0009, 0xffff0009, 0xffff0009, 0x00000000, 
0x00000000, 0xffff0009, 0xffde4600, 0xffde4600, 0xffdeb200, 0xffdeb200, 0xffdeb200, 0xffff0009, 0xffff0009, 0xffff0009, 0xffff0009, 
0xffff0009, 0xffff0009, 0xffde4600, 0xffde4600, 0xffde4600, 0xffde4600, 0xffde4600, 0xffff0009, 0xffde4600, 0xffde4600, 0xffff0009, 
0xffff0009, 0xffb30007, 0xffb30007, 0xffb30007, 0xffde4600, 0xffde4600, 0xffde4600, 0xffde4600, 0xffde4600, 0xffff0009, 0xffff0009, 
0xffff0009, 0xffb30007, 0xffb30007, 0xffb30007, 0xffde4600, 0xffde4600, 0xffb30007, 0xffb30007, 0xffb30007, 0xffff0009, 0x00000000, 
0xffff0009, 0xffff0009, 0xffff0009, 0xffb30007, 0xffb30007, 0xffb30007, 0xffb30007, 0xffb30007, 0xffff0009, 0xffff0009, 0xffff0009

};    
   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}

void draw_earth(int u, int v)
{

int new_piskel_data[121] = {

0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffffffff, 0xff00659e, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 
0x00000000, 0xffffffff, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0x00000000, 
0xffffffff, 0xffffffff, 0xff00659e, 0xffffffff, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0x00000000, 
0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0x00000000, 
0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xff00659e, 0xff00659e, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 
0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xff00659e, 0xffffffff, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e

};    
   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}





///////////////////////////////////////////
//Other sprites
///////////////////////////////////////////

void draw_chest(int u, int v) 
{
    const char* img =
        "           "
        "           "
        "  1111111  "
        " 112222211 "
        "11222222211"
        "1111YYY1111"
        "1122YYY2211"
        "11222222211"
        "11222222211"
        "11222222211"
        "11111111111";
        draw_img(u, v, img);
}

void draw_cave1(int u, int v)
{
    const char* img =
        "$4444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444";
    draw_img(u, v, img);
}
void draw_cave2(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333";
    draw_img(u, v, img);
}
void draw_cave3(int u, int v)
{
    const char* img =
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444000"
        "44444444000"
        "44444444000";
    draw_img(u, v, img);
}
void draw_cave4(int u, int v)
{
    const char* img =
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "44444444444"
        "00044444444"
        "00044444444"
        "00044444444";
    draw_img(u, v, img);
}

void draw_mud(int u, int v)
{
   const char* img = 
        "DDDDDDDDDDD"
        "DDD3333DD3D"
        "D33D33D33DD"
        "D3DDD33D33D"
        "DD333D333DD"
        "D33D33DDDD"
        "DDD333D333D"
        "DD3DDD3DD3D"
        "D3D333D33DD"
        "DDDDD33DDDD"
        "DDDDDDDDDDD";
    draw_img(u, v, img);
}