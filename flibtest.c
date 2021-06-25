#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics.h"
#include "flib.h"


SceCtrlData input;

int SetupCallbacks();
void show_errmsg(const char *errmsg);

PSP_MODULE_INFO("ttf library demo", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);


int main(void)
{
	SetupCallbacks();
	initGraphics(); 

	if(!load_font("times.ttf"))	// load "times new roman" font
	{
		show_errmsg("Could not load font file.");
		return 1;
	}

	clearScreen(0);

	set_font_color(0xff00ffff);	// yellow
	set_font_size(12);		// 12 point
	set_font_angle(0.0);		// no angle
	text_to_screen("12 point", 50, 50);

	set_font_color(0xff00ff00);	// green
	set_font_size(16);		// 16 point
	text_to_screen("16 point", 50, 100);

	set_font_angle(45.0);		// rotate 45 degrees counter-clockwise
	text_to_screen("rotated", 200, 200);

	set_font_size(60);		// 30 point
	set_font_color(0xff0000ff);	// red
	set_font_angle(90.0);		// vetical text
	text_to_screen("TOO BIG!!", 350, 310);

	sceDisplayWaitVblankStart();
	flipScreen();

	sceCtrlReadBufferPositive(&input, 1);
	while(!input.Buttons)
	{
		sceKernelDelayThread(10000);	// wait 10 milliseconds
		sceCtrlReadBufferPositive(&input, 1);
	}

	unload_font();
	sceKernelExitGame();
	return 0;
}


void show_errmsg(const char *errmsg)
{
	pspDebugScreenInit();
	pspDebugScreenSetXY(0, 2);
	pspDebugScreenPrintf("\n\n%s\n\nPress START to continue.", errmsg);

	while(!(input.Buttons & PSP_CTRL_START))
		sceCtrlReadBufferPositive(&input, 1);
}


/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();
	return 0;
}


/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}


/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}


