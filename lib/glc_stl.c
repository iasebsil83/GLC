// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//filesystem
#include "files.h"

//own header
#include "glc_stl.h"








/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GLC_STL [0.1.0] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                               STL files in GLC

        glc_stl is an utility program that allows you to load STL files into
    GLC.

    WARNING : ONLY STANDARD BINARY STL FILES ARE SUPPORTED !

    NOTE : This file is NOT required to run GLC though it is quite useful to load 3D
           structures more easily.

    14/01/2022 > [0.1.0] :
    - Created glc_stl.c/.h.

    BUGS : .
    NOTES : .

    Contact     : i.a.sebsil83@gmail.com
    Youtube     : https://www.youtube.com/user/IAsebsil83
    GitHub repo : https://github.com/iasebsil83

    Let's Code !                                  By I.A.
********************************************************************************
    LICENCE :
    glc_stl
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








// ---------------- DECLARATIONS ----------------

//glc shared variables
extern GLC_vars GLC;








// ---------------- STL ----------------

//load into scene
stl* GLC_loadSTL(char* path){
	if(!path){
		printf("RUNTIME ERROR > glc_stl.c : GLC_loadSTL() : Path is NULL.\n");
		return NULL;
	}

	//get data from file
	size_t file_size;
	char*  file_data;
	char   state = file_read(path, &file_data, &file_size);

	//error case
	if(state != FILES__SUCCESS){
		printf("RUNTIME ERROR > glc_stl.c : GLC_loadSTL() : Unable to read file '%s'.\n", path);
		return NULL;
	}

	//create new stl object
	stl* object = malloc(sizeof(stl));
	if(!object){
		printf("FATAL ERROR > glc_stl.c : GLC_loadSTL() : Computer refuses to give more memory.\n");
		exit(EXIT_FAILURE);
	}

	//get number of plaks (4 bytes after 80 bytes header)
	if(file_size < 81){
		printf("RUNTIME ERROR > glc_stl.c : GLC_loadSTL() : Not enough bytes in STL file '%s'.\n", path);
		free(object);
		free(file_data);
		return NULL;
	}
	object->plaksNbr = (
		((file_data[83] << 24) & 0xff000000) |
		((file_data[82] << 16) & 0x00ff0000) |
		((file_data[81] <<  8) & 0x0000ff00) |
		((file_data[80]      ) & 0x000000ff)
	);

	//check file size (50 bytes per plak)
	if(file_size < 84 + (object->plaksNbr)*50){
		printf("RUNTIME ERROR > glc_stl.c : GLC_loadSTL() : Not enough bytes in STL file '%s' (%d plaks).\n", path, object->plaksNbr);
		free(object);
		free(file_data);
		return NULL;
	}

	//store data
	object->data = file_data;

	return object;
}

void GLC_freeSTL(stl* object){
	if(!object){
		printf("RUNTIME ERROR > glc_stl.c : GLC_freeSTL() : Object is NULL.\n");
		return;
	}

	//free object
	free(object->data);
	free(object);
}



//display
void GLC_3DSTL(
	stl* object,
	unit px, unit py, unit pz, //position
	unit rx, unit ry, unit rz, //rotation
	unit sx, unit sy, unit sz, //scale
	color* c
){
	//error case
	if(!object){
		printf("RUNTIME ERROR > glc_stl.c : GLC_3DSTL() : Object is NULL.\n");
		return;
	}

	//color
	if(c){
		glColor4f(c->r, c->g, c->b, c->a);
	}

	//start drawing
	//glDisable(GL_LIGHTING);
	glPushMatrix();

		//position - rotation - scale
		glTranslatef(px, py, pz);
		glRotatef(rx, 1.0, 0.0, 0.0);
		glRotatef(ry, 0.0, 1.0, 0.0);
		glRotatef(rz, 0.0, 0.0, 1.0);
		glScalef(sx, sy, sz);

		//ray
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  *((GLC.currentRay)->a) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  *((GLC.currentRay)->d) );
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, *((GLC.currentRay)->s) );

		//shape

		//data following pointer
		char*  dataFromBeginingOfPlak = object->data + 84;
		float* dataInFloat;

		//object
		xyz p1, p2, p3;
		for(unsigned int n=0; n < (object->plaksNbr); n++){
			dataInFloat = (float*)dataFromBeginingOfPlak;

			//skip Normal and get Point1, Point2, Point3
			p1.x = dataInFloat[ 3];
			p1.y = dataInFloat[ 4];
			p1.z = dataInFloat[ 5];
			p2.x = dataInFloat[ 6];
			p2.y = dataInFloat[ 7];
			p2.z = dataInFloat[ 8];
			p3.x = dataInFloat[ 9];
			p3.y = dataInFloat[10];
			p3.z = dataInFloat[11];

			//plak
			glBegin(GL_TRIANGLES);
				glVertex3f(p1.x, p1.y, p1.z);
				glVertex3f(p2.x, p2.y, p2.z);
				glVertex3f(p3.x, p3.y, p3.z);
			glEnd();

			//translate following pointer (50 bytes per plak)
			dataFromBeginingOfPlak += 50;
		}

	//end drawing
	glPopMatrix();
	//glEnable(GL_LIGHTING);
}
