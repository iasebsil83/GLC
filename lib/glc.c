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

    REQUIREMENTS :
        - Linux operating system.
        - Package 'freeglut3-dev' :
                    sudo apt install freeglut3-dev

        This library is a SIMPLE graphic utility to manage 2D and 3D objects.

    BUGS  : .
    NOTES : .

    GLC is compatible with another library I made
    for PNG image manipulation : PNG.c/.h.
    It is available here :
            https://github.com/iasebsil83/C_PNG

    Contact     : i.a.sebsil83@gmail.com
    Youtube     : https://www.youtube.com/user/IAsebsil83
    GitHub repo : https://github.com/iasebsil83

    Let's Code !                                  By I.A.
******************************************************************************

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








// ---------------- INITIALIZATION ----------------

//window variables (glc only)
static int GLC_window               = -1;
static int GLC_width_2              =  0;
static int GLC_height_2             =  0;
static int GLC_timedExecution_delay = -1;

//debug
//uncomment the line below to activate debug messages
//#define DEBUG_ON
//uncomment the line below to activate deep debug messages
//#define DEEP_DEBUG_ON

//constant 3D attributes (glc only)
#define GLC_LOOK_AT_X 0.0
#define GLC_LOOK_AT_Y 0.0
#define GLC_LOOK_AT_Z 0.0
#define GLC_UP_X 0.0
#define GLC_UP_Y 1.0
#define GLC_UP_Z 0.0

//camera
xyz GLC_camPos = {
	.x = 0.0,
	.y = 0.0,
	.z = 0.0
};
xyz GLC_camRot = {
	.x = 0.0,
	.y = 0.0,
	.z = 0.0
};

//sky colors
color GLC_skyColor = {
	.r = 0,
	.g = 200,
	.b = 255
};

//rays
ambient  GLC_defaultAmbient  = {0.45, 0.45, 0.45, 1.0};
diffuse  GLC_defaultDiffuse  = { 0.7,  0.7,  0.7, 1.0};
specular GLC_defaultSpecular = { 0.8,  0.8,  0.8, 1.0};
ray      GLC_defaultRay = {
	.a = &GLC_defaultAmbient,
	.d = &GLC_defaultDiffuse,
	.s = &GLC_defaultSpecular
};

//light
light GLC_light = {
	.pos = { 50.0, 0.0, 50.0, 0.0},
	.r   = &GLC_defaultRay
};

//event variables
unsigned int   GLC_newWidth    = 0; //resize
unsigned int   GLC_newHeight   = 0;
unsigned int   GLC_width       = 0;
unsigned int   GLC_height      = 0;
         int   GLC_keyState    = 0; //keyboard
unsigned short GLC_key         = 0;
         int   GLC_mouseState  = 0; //mouse
         int   GLC_mouseButton = 0;
         int   GLC_mouseScroll = 0;
         int   GLC_mouseX      = 0;
         int   GLC_mouseY      = 0;

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
static void GLCL_display(){

	//clear screen
	glClearColor(
		(unit)(GLC_skyColor.r),
		(unit)(GLC_skyColor.g),
		(unit)(GLC_skyColor.b),
		(unit)(GLC_skyColor.a)
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(CST4);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set viewpoint
	gluLookAt(
		GLC_camPos.x,  GLC_camPos.y,  GLC_camPos.z,
		GLC_LOOK_AT_X, GLC_LOOK_AT_Y, GLC_LOOK_AT_Z,
		GLC_UP_X,      GLC_UP_Y,      GLC_UP_Z
	);

	//light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION,    GLC_light.pos      );
	glLightfv(GL_LIGHT0, GL_AMBIENT,  *((GLC_light.r  )->s) );
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  *((GLC_light.r  )->s) );
	glLightfv(GL_LIGHT0, GL_SPECULAR, *((GLC_light.r  )->s) );

	//extern program display
	GLC_event(GLC_DISPLAY);
	glutSwapBuffers();
}



//keyboard
static void GLCL_keyPressed(GLubyte g, int x,int y){
	GLC_key = g;
	GLC_keyState = GLC_KEY_PRESSED;
	GLC_event(GLC_KEYBOARD);
}

static void GLCL_keyPressed_special(int keyCode, int x,int y){
	GLC_key = 256 + (unsigned char)keyCode;
	GLC_keyState = GLC_KEY_PRESSED;
	GLC_event(GLC_KEYBOARD);
}

static void GLCL_keyReleased(GLubyte g, int x,int y){
	GLC_key = g;
	GLC_keyState = GLC_KEY_RELEASED;
	GLC_event(GLC_KEYBOARD);
}

static void GLCL_keyReleased_special(int keyCode, int x,int y){
	GLC_key = 256 + (unsigned char)keyCode;
	GLC_keyState = GLC_KEY_RELEASED;
	GLC_event(GLC_KEYBOARD);
}



//mouse
static void GLCL_mouseButton(int button, int state, int x,int y){
	GLC_mouseX = x;
	GLC_mouseY = GLC_height - y;
	GLC_mouseState = state;

	//scroll
	if(button == 3 || button == 4){
		if(state == GLC_MOUSE_PRESSED){
			GLC_mouseScroll = button;
			GLC_event(GLC_MOUSE_SCROLL);
		}
	}else{
		GLC_mouseButton = button;
		GLC_event(GLC_MOUSE_CLICK);
	}
}

static void GLCL_mouseMoved(int x,int y){
	GLC_mouseX = x;
	GLC_mouseY = GLC_height - y;
	usleep(1);
	if(GLC_mouseScroll == 0){
		GLC_event(GLC_MOUSE_MOVE);
	}else{
		GLC_mouseScroll = 0;
	}
}



//resize
static void GLCL_reshape(int newWidth,int newHeight){

	//raise event with old values
	GLC_newWidth  = newWidth;
	GLC_newHeight = newHeight;
	GLC_event(GLC_RESIZE);
	GLC_width  = newWidth;
	GLC_height = newHeight;

	//set new values
	GLC_width    = newWidth;
	GLC_width_2  = newWidth/2;
	GLC_height   = newHeight;
	GLC_height_2 = newHeight/2;

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
	return x >= 0 && x < GLC_width && y >= 0 && y < GLC_height;
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
	int   argc   = 0;
	char* argv_p = NULL;
	char** argv  = &argv_p;

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

	//some settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);

	//init color & depth buffers
	GLC_width    = width;
	GLC_width_2  = width/2;
	GLC_height   = height;
	GLC_height_2 = height/2;

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
