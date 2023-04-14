//=================================================================
// The speech header file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#ifndef SPEECH_H
#define SPEECH_H

/**
 * Display a speech bubble.
 */
void speech(const char* line1, const char* line2);

void draw_text(const char* line1, int line, int offset, int color);

/**
 * Display a long speech bubble, with scrolling.
 * 
 * @param lines The actual lines of text to display
 * @param n The number of lines to display.
 */
void long_speech(const char* lines[], int n);

//void draw_speech_bubble();
//void draw_speech_line(const char* line, int which);

#endif // SPEECH_H
