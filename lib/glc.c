// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

//own header
#include "glc.h"








/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GLC [0.1.0] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                              Graphic Library Core

        GLC is a graphic library for Linux using OpenGL, GLU, GLUT and some
    other libraries I made to make it the MOST SIMPLE AS POSSIBLE.

        With GLC, you can manage any kind of computer event (keyboard press,
    mouse moving, mouse clicking, window resizing...) and display objects on
    screen in both 2D and 3D.

    This library is composed of 10 files :
        - glc.c/.h           (core)
        - glc_objects2D.c/.h
        - glc_objects3D.c/.h
        - glc_stl.c/.h       (not necessary but useful to load 3D objects quickly)
        - glc_specials.c/.h  (some other useful stuff)

    Note that some files requires other libraries :
        - glc_objects2D: PNG.c/.h
        - glc_objects3D: PNG.c/.h
        - glc_stl      : files.c/.h

    These libraries are also creation of mine so you can check them out at :
                    https://github.com/iasebsil83/C_PNG
                    https://github.com/iasebsil83/C_files

    GLC REQUIREMENTS :
        - Linux operating system.
        - Package 'freeglut3-dev':
                    sudo apt install freeglut3-dev
        - Package 'libpng':
                    sudo apt install libpng-dev (for the use of PNG.c/.h only)

    BUGS  : .
    NOTES : .

    Contact     : i.a.sebsil83@gmail.com
    Youtube     : https://www.youtube.com/user/IAsebsil83
    GitHub repo : https://github.com/iasebsil83

    Let's Code !                                  By I.A.
*****************************************************************************

    LICENCE :

    GLC
    Copyright (C) 2021  Sebastien SILVANO
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.

    If not, see <https://www.gnu.org/licenses/>.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */








// ---------------- DEFAULT VALUES ----------------

//colors
color* GLC_colors[8];
static color red     = {.r=255, .g=0,   .b=0,   .a=255};
static color green   = {.r=0,   .g=255, .b=0,   .a=255};
static color blue    = {.r=0,   .g=0,   .b=255, .a=255};
static color magenta = {.r=255, .g=0,   .b=255, .a=255};
static color cyan    = {.r=255, .g=255, .b=0,   .a=255};
static color yellow  = {.r=0,   .g=255, .b=255, .a=255};
static color white   = {.r=255, .g=255, .b=255, .a=255};
static color black   = {.r=0,   .g=0,   .b=0,   .a=255};

//sky color
color GLC_DEFAULT_skyColor = {.r=0, .g=100, .b=155};

//ray
ambient  GLC_DEFAULT_ambient  = {0.45, 0.45, 0.45, 1.0};
diffuse  GLC_DEFAULT_diffuse  = { 0.3,  0.1,  0.5, 1.0};
specular GLC_DEFAULT_specular = { 0.1,  0.4,  0.3, 1.0};
ray      GLC_DEFAULT_ray      = {
	.a = &GLC_DEFAULT_ambient,
	.d = &GLC_DEFAULT_diffuse,
	.s = &GLC_DEFAULT_specular
};

//light
light GLC_DEFAULT_light = {
	.p = {500.0, 500.0, 500.0, 0.0},
	.r = &GLC_DEFAULT_ray
};

//position - rotation - scale
prs GLC_DEFAULT_prs = {
	.pos = { .x=0, .y=0, .z=0 },
	.rot = { .x=0, .y=0, .z=0 },
	.sca = { .x=1, .y=1, .z=1 }
};








// ---------------- INITIALIZATION ----------------

//window variables (glc only)
static int GLC_window               = -1;
static int GLC_timedExecution_delay = -1;

//constant 3D attributes (glc only)
#define GLC_UP_X 0.0
#define GLC_UP_Y 1.0
#define GLC_UP_Z 0.0

//camera
GLC_vars GLC = {

	//scene
	.camPos       = { .x=0, .y=0, .z=0 },
	.camRot       = { .x=0, .y=0, .z=0 },
	.skyColor     = &GLC_DEFAULT_skyColor,
	.currentRay   = &GLC_DEFAULT_ray,
	.currentLight = &GLC_DEFAULT_light,

	//resize
	.width        = 0,
	.height       = 0,
	.width_2      = 0, // width/2
	.height_2     = 0, // height/2
	.newWidth     = 0,
	.newHeight    = 0,

	//keyboard
	.keyState     = 0,
	.key          = 0,

	//mouse
	.mouseX       = 0,
	.mouseY       = 0,
	.prevMouseX   = 0,
	.prevMouseY   = 0,
	.mouseState   = 0,
	.mouseButton  = 0,
	.mouseScroll  = 0
};

//event handler
extern void GLC_event(int event);

//constants <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#define CST1 60
#define CST2 1
#define CST3 1200
#define CST4 8








// ---------------- LOCAL EVENT HANDLERS (S3DEL) ----------------

//timed executions
static void GLCL_timedExecution(int i){
	if(i < 0)
		GLC_refresh();
	else{
		if(GLC_timedExecution_delay >= 0){
			glutTimerFunc(
				(unsigned int)GLC_timedExecution_delay,
				GLCL_timedExecution,
				GLC_timedExecution_delay
			);
			GLC_event(GLC_TIMER);
		}
	}
}



//display
static void GLCL_display() {

	//clear screen
	glClearColor(
		(unit)((GLC.skyColor)->r),
		(unit)((GLC.skyColor)->g),
		(unit)((GLC.skyColor)->b),
		(unit)((GLC.skyColor)->a)
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(CST4);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set viewpoint
	float cosY = cos(GLC.camRot.y);
	float sinY = sin(GLC.camRot.y);
	gluLookAt(
		GLC.camPos.x,      GLC.camPos.y, GLC.camPos.z,
		GLC.camPos.x+sinY, GLC.camPos.y, GLC.camPos.z-cosY,
		GLC_UP_X,          GLC_UP_Y,     GLC_UP_Z
	);

	//light
	//glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION,     (GLC.currentLight)->p        );
	glLightfv(GL_LIGHT0, GL_AMBIENT,  *(( (GLC.currentLight)->r  )->a) );
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  *(( (GLC.currentLight)->r  )->d) );
	glLightfv(GL_LIGHT0, GL_SPECULAR, *(( (GLC.currentLight)->r  )->s) );

	//extern program display
	GLC_event(GLC_DISPLAY);
	glutSwapBuffers();
}



//keyboard
static void GLCL_keyPressed(GLubyte g, int x,int y){
	GLC.key      = g;
	GLC.keyState = GLC_KEY_PRESSED;
	GLC_event(GLC_KEYBOARD);
}

static void GLCL_keyPressed_special(int keyCode, int x,int y){
	GLC.key      = 256 + (unsigned char)keyCode;
	GLC.keyState = GLC_KEY_PRESSED;
	GLC_event(GLC_KEYBOARD);
}

static void GLCL_keyReleased(GLubyte g, int x,int y){
	GLC.key      = g;
	GLC.keyState = GLC_KEY_RELEASED;
	GLC_event(GLC_KEYBOARD);
}

static void GLCL_keyReleased_special(int keyCode, int x,int y){
	GLC.key      = 256 + (unsigned char)keyCode;
	GLC.keyState = GLC_KEY_RELEASED;
	GLC_event(GLC_KEYBOARD);
}



//mouse
static void GLCL_mouseButton(int button, int state, int x,int y){

	//store previous position
	GLC.prevMouseX = GLC.mouseX;
	GLC.prevMouseX = GLC.mouseX;

	//get new position
	GLC.mouseX     = x;
	GLC.mouseY     = GLC.height - y;
	GLC.mouseState = state;

	//scroll
	if(button == 3 || button == 4){
		if(state == GLC_MOUSE_PRESSED){
			GLC.mouseScroll = button;
			GLC_event(GLC_MOUSE_SCROLL);
		}
	}else{
		GLC.mouseButton = button;
		GLC_event(GLC_MOUSE_CLICK);
	}
}

static void GLCL_mouseMoved(int x,int y){

	//store previous position
	GLC.prevMouseX = GLC.mouseX;
	GLC.prevMouseX = GLC.mouseX;

	//get new position
	GLC.mouseX = x;
	GLC.mouseY = GLC.height - y;

	//scroll reset
	usleep(1);
	if(GLC.mouseScroll == 0){
		GLC_event(GLC_MOUSE_MOVE);
	}else{
		GLC.mouseScroll = 0;
	}
}



//resize
static void GLCL_reshape(int newWidth,int newHeight){

	//raise event with old values
	GLC.newWidth  = newWidth;
	GLC.newHeight = newHeight;
	GLC_event(GLC_RESIZE);
	GLC.width  = newWidth;
	GLC.height = newHeight;

	//set new values
	GLC.width    = newWidth;
	GLC.width_2  = newWidth/2;
	GLC.height   = newHeight;
	GLC.height_2 = newHeight/2;

	//reshape
	glViewport(0,0, newWidth,newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(CST1, (float)newWidth/newHeight, CST2, CST3);

	//refresh display
	GLC_refresh();
}








// ---------------- GENERAL TOOLS ----------------

//useful
void GLC_setThickness(unit thickness){
	glPointSize(thickness);
	glLineWidth(thickness);
}

int GLC_inScreen(unit x,unit y){
	return x >= 0 && x < GLC.width && y >= 0 && y < GLC.height;
}

void GLC_setTimer(int ms){
	if(GLC_timedExecution_delay < 0 && ms >= 0)
		glutTimerFunc(
			(unsigned int)ms,
			GLCL_timedExecution,
			ms
		);

	//set new timedExecution delay
	GLC_timedExecution_delay = ms;
}








// ---------------- BASICS -----------------

//init
void GLC_init(const char* name, unit width,unit height){
	int    argc   = 0;
	char*  argv_p = NULL;
	char** argv   = &argv_p;

	//error case
	if(name == NULL){
		printf("RUNTIME ERROR > glc.c : GLC_init() : Cannot init window, name is NULL.\n");
		return;
	}

	//init window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
	GLC_window = glutCreateWindow(name);

	//init colors
	GLC_colors[RED]     = &red;
	GLC_colors[GREEN]   = &green;
	GLC_colors[BLUE]    = &blue;
	GLC_colors[MAGENTA] = &magenta;
	GLC_colors[CYAN]    = &cyan;
	GLC_colors[YELLOW]  = &yellow;
	GLC_colors[WHITE]   = &white;
	GLC_colors[BLACK]   = &black;

	//some settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);

	//init color & depth buffers
	GLC.width    = width;
	GLC.width_2  = width/2;
	GLC.height   = height;
	GLC.height_2 = height/2;

	//set local GLC event handlers (GLCL)
	glutDisplayFunc      (GLCL_display            );
	glutKeyboardFunc     (GLCL_keyPressed         );
	glutSpecialFunc      (GLCL_keyPressed_special );
	glutKeyboardUpFunc   (GLCL_keyReleased        );
	glutSpecialUpFunc    (GLCL_keyReleased_special);
	glutMouseFunc        (GLCL_mouseButton        );
	glutMotionFunc       (GLCL_mouseMoved         );
	glutPassiveMotionFunc(GLCL_mouseMoved         );
	glutReshapeFunc      (GLCL_reshape            );
}



//start - stop
void GLC_stop(){

	//stop 2D engine
	glutDestroyWindow(GLC_window);
	exit(EXIT_SUCCESS);
}
