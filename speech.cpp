//=================================================================
// The speech class file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "speech.h"

#include "globals.h"
#include "hardware.h"

///////////////////////////////
//Static function declarations
///////////////////////////////
/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line, int which);


///////////////////////////////
//Drawing function declarations
///////////////////////////////


//***
// HINT: for this function and below: Check out the ULCD demo in the docs to see what
// uLCD methods you can use to draw graphics 

//Link: https://os.mbed.com/users/4180_1/notebook/ulcd-144-g2-128-by-128-color-lcd/
//***


void draw_speech_bubble()
{
    //1. Draw a speech bubble at the bottom of the screen 
    // Hint: You can stack ULCD rectangles to make a border
    uLCD.filled_rectangle(3, 113 , 128, 93, WHITE);

    uLCD.filled_rectangle(3,    93, 128,  94, WHITE); // Top
    //uLCD.filled_rectangle(0,   113, 128, 112, WHITE); // Bottom
    //uLCD.filled_rectangle(0,    113,   1, 93, WHITE); // Left
    //uLCD.filled_rectangle(128,  113, 126, 93, WHITE); // Right
}

void erase_speech_bubble()
{
    uLCD.filled_rectangle(3, 113 , 128, 93, BLACK);
    uLCD.filled_rectangle(3,    93, 128,  94, BLACK);
    wait(0.05);
    //1. Erase the speech bubble at the bottom of the screen
    // Hint: You can overwrite the bubble with a empty (black) one
}

void draw_speech_line(const char* line, int which)
{
    //1. Set the location which line of text will go the uLCD
    // Hint: Change the y coordinate based on which line (top or bottom)

    //2. For each character in the text, write it to uLCD
    for (int i = 0; line[i] && i < 17; i++) //We can simplify by limiting each line to 17 char
    {   //uLCD.text_char(line[i], 10, 10, WHITE);
        uLCD.text_char(line[i], i+1 , which, WHITE);
        wait_ms(15); 
    }
}

void speech_bubble_wait()
{
    // 1. Keep waiting until the action button is pressed 
    //   Hint: What type of loop can we use to stay until a condition is met?
    Timer wait;
    wait.start();
    int time;
    GameInputs inputs;
    int toggle = 0;

    do {
        // wait until ~1.5 seconds pass before being able to remove
        inputs = read_inputs();
        time = wait.read_ms();

        wait_ms(75);
        toggle = !toggle;
        if (toggle) uLCD.filled_circle(120,121,4,RED);
        else uLCD.filled_circle(120,121,4,BLACK);
        inputs = read_inputs();
    } while(inputs.b1 || !(time > 300 && !inputs.b1));

    uLCD.filled_circle(120,121,4,BLACK);
    return;
}

void speech(const char* line1, const char* line2)
{
    // 1. Place the two lines into an array of lines
    const char* lines[] = {line1, line2};
    // 2. Pass in to long_speech with the corresponding number of lines
    long_speech(lines, 2);
    return;
}

void draw_text(const char* line1, int line, int offset, int color) {
     for (int i = 0; line1[i] && i < 17; i++) //We can simplify by limiting each line to 17 char
    {   //uLCD.text_char(line[i], 10, 10, WHITE);
        uLCD.text_char(line1[i], i+offset , line, color);
    }
}

void long_speech(const char* lines[], int n)
{

    //1. Create a speech bubble
    draw_speech_bubble();

    int line = 12;
    //2. For each lines, display only two lines at a time
    //   If two lines are displayed, make sure to wait (call the wait function)
    for (int i = 0; i < n; i++) {
        draw_speech_line(lines[i], line++);
    }
    speech_bubble_wait();
    //3. Erase the speech bubble when you are done
    erase_speech_bubble();
    return;
}

