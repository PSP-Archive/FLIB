//	flib.c - A TrueType font library for the PSP
//
//	Based on the freetype2 tutorials and example code
//
//	Copyright 2006 samedi1971@yahoo.com
//
//	Requirements:	PSP graphics library by Psilocybeing
//				libpng for PSP
//				libfreetype2 for PSP


#ifndef FLIB_H
#define FLIB_H

// error codes
#define FLIB_ERR_CANTINIT	1	// problem initializing freetype 2
#define FLIB_ERR_CANTOPEN	2	// problem finding or loading .ttf file
#define FLIB_ERR_MEMORY		3	// ran out of memory
#define FLIB_ERR_INVALIDFONT	4	// attempt to use bad/empty font
#define FLIB_ERR_BADSIZE	5	// requested size out of range


// definitions
typedef void *FLIB_FONT;

// functions
void set_font_color(Color color);
void set_font_angle(double angle);
int set_font_size(int size);
FLIB_FONT load_font(char *filename);
void unload_font(void);
void text_to_screen(char *text, int x, int y);
void text_to_image(char *text, Image *image, int x, int y);

#endif
