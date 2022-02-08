//standard
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//glc
#include "../lib/glc_all.h"








// ---------------- DECLARATIONS ----------------

//GLC shared variables
extern GLC_vars GLC;
extern color*   GLC_colors[8];

//GLC default values used
extern ray GLC_DEFAULT_ray;
extern prs GLC_DEFAULT_prs;

//camera movements
#define CAMERA_MOVE_STEP  1
#define CAMERA_ANGLE_STEP 0.04

//custom rays
ambient  myAmbient  = {0.913, 0.71, 0.51, 1.0};
diffuse  myDiffuse  = {0.1,   0.1,  0.1,  1.0};
specular mySpecular = {1.0,   1.0,  1.0,  1.0};
ray myRay = {
	.a = &myAmbient,
	.d = &myDiffuse,
	.s = &mySpecular
};








// ---------------- SCENE ----------------

//pictures
PNG* creeper;
PNG* satellite;

//brain by nailbansal : https://www.thingiverse.com/thing:5197301/files
stl* brain_obj;
prs  brain_prs = {
	.pos = { .x=10,   .y=1,    .z=25   },
	.rot = { .x=0,    .y=0,    .z=0    },
	.sca = { .x=0.01, .y=0.01, .z=0.01 }
};

//mando by PeteBaker : https://www.thingiverse.com/thing:4133665/files
stl* mando_obj;
prs  mando_prs = {
	.pos = { .x=150,  .y=1,   .z=25   },
	.rot = { .x=M_PI, .y=0,   .z=0    },
	.sca = { .x=0.5,  .y=0.5, .z=0.5  }
};

//mora coins by fkiliver : https://www.thingiverse.com/thing:4801477/files
stl* mora_obj;
prs  mora_prs = {
	.pos = { .x=-10, .y=1, .z=20 },
	.rot = { .x=0,   .y=0, .z=0  },
	.sca = { .x=1,   .y=1, .z=1  }
};

stl* cube_obj;
prs cube_prs = {
	.pos = { .x=0, .y=0,   .z=0 },
	.rot = { .x=0,   .y=0,   .z=0  },
	.sca = { .x=10000, .y=10000, .z=10000}
};

//ground
xyz ground_size = { .x=1000, .y=-5, .z=1000 };

//myBox
prs myBox_prs = {
	.pos = { .x=10, .y=1, .z=5 },
	.rot = { .x=0,  .y=0, .z=0 },
	.sca = { .x=1,  .y=1, .z=1 }
};
xyz myBox_size = { .x=20, .y=30, .z=40 };

//plane1
prs plane1_prs = {
	.pos = { .x=20, .y=1,    .z=40 },
	.rot = { .x=0,  .y=M_PI, .z=0  },
	.sca = { .x=1,  .y=1,    .z=1  }
};
xy plane1_size = { .x=2, .y=3 };



//init structures
void loadStructures(){

	//load pictures
	creeper   = png_read("png/Creeper.png");
	satellite = png_read("png/Satellite.png");

	//load stl
	/*brain_obj = GLC_loadSTL("stl/Brain.stl");
	mando_obj = GLC_loadSTL("stl/Mandalorian.stl");
	mora_obj  = GLC_loadSTL("stl/Mora.stl");*/
	//cube_obj = GLC_loadSTL("stl/cube.stl");
}








// ---------------- EVENTS ----------------

//events
void GLC_event(int event){
	switch(event){

		//display
		case GLC_DISPLAY:

			//plane1
			GLC.currentRay = &GLC_DEFAULT_ray;
			GLC_3DPlane(
				XY(plane1_size),
				PRS(plane1_prs),
				GLC_colors[MAGENTA], GLC_TEX_COLOR
			);

			//ground
			GLC_3DHexaedron(
				XYZ(ground_size),
				PRS(GLC_DEFAULT_prs),
				GLC_colors[GREEN], GLC_TEX_COLOR
			);

			//myCube
			GLC_3DHexaedron(
				XYZ(myBox_size),
				PRS(myBox_prs),
				GLC_colors[BLUE], GLC_TEX_COLOR
			);
			
			/*//brain
			GLC.currentRay = &myRay;
			GLC_3DSTL(
				brain_obj,
				PRS(brain_prs),
				GLC_colors[RED]
			);*/

			//cube
			/*GLC.currentRay = &GLC_DEFAULT_ray;
			GLC_3DSTL(
				cube_obj,
				PRS(cube_prs),
				GLC_colors[RED]
			);*/

			/*//mando
			GLC_3DSTL(
				mando_obj,
				PRS(mando_prs),
				GLC_colors[BLACK]
			);

			//mora
			GLC_3DSTL(
				mora_obj,
				PRS(mora_prs),
				GLC_colors[WHITE]
			);*/
		break;

		//keyboard
		case GLC_KEYBOARD:
			switch(GLC.key){

				//camera position
				case GLC_KEY_Z:
				case GLC_KEY_z:
					GLC.camPos.z -= CAMERA_MOVE_STEP;
				break;
				case GLC_KEY_S:
				case GLC_KEY_s:
					GLC.camPos.z += CAMERA_MOVE_STEP;
				break;
				case GLC_KEY_Q:
				case GLC_KEY_q:
					GLC.camPos.x -= CAMERA_MOVE_STEP;
				break;
				case GLC_KEY_D:
				case GLC_KEY_d:
					GLC.camPos.x += CAMERA_MOVE_STEP;
				break;
				case GLC_KEY_A:
				case GLC_KEY_a:
					GLC.camPos.y -= CAMERA_MOVE_STEP;
				break;
				case GLC_KEY_E:
				case GLC_KEY_e:
					GLC.camPos.y += CAMERA_MOVE_STEP;
				break;



				//myBox position
				case GLC_KEY_O:
				case GLC_KEY_o:
					myBox_prs.pos.z -= 1;
				break;
				case GLC_KEY_L:
				case GLC_KEY_l:
					myBox_prs.pos.z += 1;
				break;
				case GLC_KEY_K:
				case GLC_KEY_k:
					myBox_prs.pos.x -= 1;
				break;
				case GLC_KEY_M:
				case GLC_KEY_m:
					myBox_prs.pos.x += 1;
				break;
				case GLC_KEY_I:
				case GLC_KEY_i:
					myBox_prs.pos.y -= 1;
				break;
				case GLC_KEY_P:
				case GLC_KEY_p:
					myBox_prs.pos.y += 1;
				break;


				//myBox size
				case GLC_KEY_8:
					myBox_size.z -= 10;
				break;
				case GLC_KEY_5:
					myBox_size.z += 10;
				break;
				case GLC_KEY_4:
					myBox_size.x -= 10;
				break;
				case GLC_KEY_6:
					myBox_size.x += 10;
				break;
				case GLC_KEY_7:
					myBox_size.y -= 10;
				break;
				case GLC_KEY_9:
					myBox_size.y += 10;
				break;
			}
			GLC_refresh();
		break;



		//mouse
		case GLC_MOUSE_MOVE:

			//camera rotation Y
			if(GLC.mouseX != GLC.prevMouseX){
				if(GLC.mouseX > GLC.prevMouseX){
					GLC.camRot.y += CAMERA_ANGLE_STEP;
				}else{
					GLC.camRot.y -= CAMERA_ANGLE_STEP;
				}
				GLC_refresh();
			}

			//camera rotation X
			if(GLC.mouseY != GLC.prevMouseY){
				if(GLC.mouseY > GLC.prevMouseY){
					GLC.camRot.x += CAMERA_ANGLE_STEP;
				}else{
					GLC.camRot.x -= CAMERA_ANGLE_STEP;
				}
				GLC_refresh();
			}
		break;

		//timer
		case GLC_TIMER:
		break;
	}
}








// ---------------- EXECUTION ----------------

//main
int main(int argc, char** argv){

	//load 3D structures
	loadStructures();

	//init window
	GLC_init("Program Name [V.V.V]", 800,600);

	//main loop
	GLC_start();

	return EXIT_SUCCESS;
}
