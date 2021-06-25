FLIB - A PSP Truetype font processing library based on freetype2

Version 1.0


Purpose:

This library is intended to simplify the use of truetype fonts.
Learning to use the freetype library can be very confusing.  The
flib library uses freetype example code and PSP graphics code to
make advanced text development very easy.


Limitations:

This version is very slow if you need to generate a lot of text
quickly, or if you use it to redraw text with every graphical frame.
There is no font cache included, so every single character is
loaded from the font file individually every time.  This is very
inefficient and should be used infrequently.  It is much better to
render text to an image and then blit text from the image to the
screen when needed.  Future flib versions will include some form
of font cache to speed things up.

This version is limited to one font at a time and there is no
support for switching to bold or italic text within a font.  Again,
future versions will support both.


Contents:

flib.c		The library routines used to load and render fonts.
flib.h		Header for inclusion in your programs.
flibtest.c	An example program showing how to use flib.
Makefile	An example makefile used to compile the library and
		the flibtest example.
times.ttf	New times roman font required for the flibtest example.

graphics.c	}
graphics.h	} - These files are Psilocybeing's graphic library which
framebuffer.c	}   is used to render the fonts.
framebuffer.h	}


Setting up the environment for flib:

Flib requires the freetype2 library compiled for the PSP in your
development environment.  This is available from the ps2dev.org SVN
repository.  Compiling freetype2 requires the libtool library which
must be installed first.


Installing libtool for Cygwin:

Run the Cygwin setup software from www.cygwin.com and find libtool
under the development section.  Select and install it.  No other
action should be necessary for libtool.


Installing libtool for linux or other environments:

Libtool should be available for all linux flavors, OSX, and any other
environment that supports PSP development.  Specific details are left
to the reader.  Google should be a big help.


Installing the freetype library:

From your Cygwin/Linux/OSX command prompt, type the following command
(assumes you have "svn" installed):

svn co svn://svn.ps2dev.org/psp/trunk/freetype

Enter the newly created freetype directory and type the following commands
or cut and paste:

sh autogen.sh
LDFLAGS="-L$(psp-config --pspsdk-path)/lib -lc -lpspuser" \
./configure --host psp --prefix=$(psp-config --psp-prefix)
make
make install


Compiling the flibtest example:

Install all files from flib.zip to a new directory.  If your PSPSDK
development environment is set up correctly all you need to do is
type "make" in this directory.  If successful it will create a 1.0/2.0+
PSP executable named EBOOT.PBP and will also create a flibtest and
flibtest% kxploit set for 1.5 PSPs.


Installing the resulting executables on your 1.5 PSP:

Copy the flibtest and flibtest% directories to the PSP\GAME folder on your
PSP.  Then copy times.ttf to PSP\GAME\flibtest.


Installing the resulting executables on your other firmwares:

Create a flibtest directory in PSP\GAME on your PSP.  Copy EBOOT.PBP and
times.ttf to PSP\GAME\flibtest.


Understanding the example code:

It is assumed that the reader already has at least a basic understanding of
developing in C for the PSP.  Only code directly relating to use of the flib
library will be covered.

#include "flib.h"

This line includes the flib header file to allow your code to call library
functions.

	if(!load_font("times.ttf"))	// load "times new roman" font
	{
		show_errmsg("Could not load font file.");
		return 1;
	}

This section attempts to load a font from the file times.ttf.  The
load_font() function returns zero (NULL) if there is any problem with
initializing the freetype library or loading the font file.  On success
a pointer to a FLIB_FONT handle is returned (currently unimplemented).

	set_font_color(0xff00ffff);	// yellow
	set_font_size(12);		// 12 point
	set_font_angle(0.0);		// no angle
	text_to_screen("12 point", 50, 50);

These four lines set up and print our first string of example text.  A
yellow color is selected, size is set to 12 point, and the angle is 0 degrees
for straight left to right text at 50 pixels to the right of the left edge
of the screen, and 50 pixels down from the top edge.  The result is the text
"12 point" displayed in yellow in the top left corner of the screen.

	set_font_color(0xff00ff00);	// green
	set_font_size(16);		// 16 point
	text_to_screen("16 point", 50, 100);

These lines demonstrate that text color and size are changed while the angle
is left unchanged.  The result is a bigger green text string below the first
string.

	set_font_angle(45.0);		// rotate 45 degrees counter-clockwise
	text_to_screen("rotated", 200, 200);

Now the color and size are left alone, but the angle is changed to 45 degrees.
Rotation is counter-clockwise so the text is printed near the middle of the
screen and angled upward.

	set_font_size(60);		// 30 point
	set_font_color(0xff0000ff);	// red
	set_font_angle(90.0);		// vertical text
	text_to_screen("TOO BIG!!", 350, 310);

All options are changed again this time.  These lines demonstrate that rendering
text out of bounds (outside screen or image dimensions) will not crash or harm
the system.  Notice that with such a large font and a Y value of 310 (the PSP
screen is only 272 pixels from top to bottom) the text is cut off at both ends.

	unload_font();

After waiting for any button input, the program is finished, so the font is
unloaded to free allocated memory.


Planning for future versions of flib:

The existing functions should not change in the future as features are added.
Font cache options and support for multiple fonts may require new functions to
be added, but will otherwise be handled automatically.  Any code written for the
current version should work as-is with future versions.