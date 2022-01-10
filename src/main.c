//standard
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//glc
#include "../lib/glc_all.h"








// -------- DECLARATIONS --------

//GLC shared variables
extern unsigned int   GLC_width;       //resize
extern unsigned int   GLC_height;
extern unsigned int   GLC_newWidth;
extern unsigned int   GLC_newHeight;
extern          int   GLC_keyState;    //keyboard
extern unsigned short GLC_key;
extern          int   GLC_mouseX;      //mouse
extern          int   GLC_mouseY;
extern          int   GLC_mouseButton;
extern          int   GLC_mouseScroll;
extern          int   GLC_mouseState;
extern          xyz   GLC_camPos;    //3D attributes
extern          xyz   GLC_camRot;
extern          xyz   GLC_lookAt;
extern          xyz   GLC_light;

//rays
ambient  myAmbient  = {0.913, 0.71, 0.51, 1.0};
diffuse  myDiffuse  = {0.1,   0.1,  0.1,  1.0};
specular mySpecular = {0.0,   0.0,  0.0,  1.0};








// -------- SCENE --------

//colors
color red     = {.r=255, .g=0,   .b=0,   .a=255};
color green   = {.r=0,   .g=255, .b=0,   .a=255};
color blue    = {.r=0,   .g=0,   .b=255, .a=255};
color magenta = {.r=255, .g=0,   .b=255, .a=255};
color yellow  = {.r=255, .g=255, .b=0,   .a=255};
color cyan    = {.r=0,   .g=255, .b=255, .a=255};
color white   = {.r=255, .g=255, .b=255, .a=255};
color black   = {.r=0,   .g=0,   .b=0,   .a=255};

//ground
unit ground_lx = 100;
unit ground_ly = 1;
unit ground_lz = 100;

//myCube
unit myCube_px = 1;
unit myCube_py = 1;
unit myCube_pz = 1;
unit myCube_rx = 0.0;
unit myCube_ry = 0.0;
unit myCube_rz = 0.0;
unit myCube_lx = 20;
unit myCube_ly = 30;
unit myCube_lz = 40;

//user
float   ANGLE  =  90*(M_PI/180);
#define RADIUS   100








// ---- EVENTS ----

//events
void GLC_event(int event){
	switch(event){

		//display
		case GLC_DISPLAY:

			//ground
			GLC_3DHexaedron(
				        0,         0,         0,
				        0,         0,         0,
				ground_lx, ground_ly, ground_lz,
				&green
			);

			//myCube
			GLC_3DHexaedron(
				myCube_px, myCube_py, myCube_pz,
				myCube_rx, myCube_ry, myCube_rz,
				myCube_lx, myCube_ly, myCube_lz,
				&blue
			);
		break;

		//keyboard
		case GLC_KEYBOARD:
			switch(GLC_key){

				//camera
				case GLC_KEY_Z:
				case GLC_KEY_z:
					GLC_camPos.z -= 3;
					GLC_lookAt.z -= 3;
				break;
				case GLC_KEY_S:
				case GLC_KEY_s:
					GLC_camPos.z += 3;
					GLC_lookAt.z +=3;
				break;
				case GLC_KEY_Q:
				case GLC_KEY_q:
					GLC_camPos.x -= 3;
					GLC_lookAt.x -= 3;
				break;
				case GLC_KEY_D:
				case GLC_KEY_d:
					GLC_camPos.x += 3;
					GLC_lookAt.x += 3;
				break;
				case GLC_KEY_A:
				case GLC_KEY_a:
					GLC_camPos.y -= 3;
					GLC_lookAt.y -= 3;
				break;
				case GLC_KEY_E:
				case GLC_KEY_e:
					GLC_camPos.y += 3;
					GLC_lookAt.y += 3;
				break;



				//myCube
				case GLC_KEY_O:
				case GLC_KEY_o:
					myCube_pz -= 0.5;
				break;
				case GLC_KEY_L:
				case GLC_KEY_l:
					myCube_pz += 0.5;
				break;
				case GLC_KEY_K:
				case GLC_KEY_k:
					myCube_px -= 0.5;
				break;
				case GLC_KEY_M:
				case GLC_KEY_m:
					myCube_px += 0.5;
				break;
				case GLC_KEY_I:
				case GLC_KEY_i:
					myCube_py -= 0.5;
				break;
				case GLC_KEY_P:
				case GLC_KEY_p:
					myCube_py += 0.5;
				break;

			}
			GLC_refresh();
		break;

		//timer
		case GLC_TIMER:
		break;
	}
}








// ---- EXECUTION ----

//main
int main(int argc, char** argv){

	//set position
	GLC_camPos.x = RADIUS*cos(ANGLE);
	GLC_camPos.y = 0.0;
	GLC_camPos.z = RADIUS*sin(ANGLE);

	//init window
	GLC_init("Program Name [V.V.V]", 800,600);

	//main loop
	GLC_start();

	return EXIT_SUCCESS;
}
