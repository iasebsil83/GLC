// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//filesystem
#include "files.h"

//own header
#include "glc_stl.h"
#include "glc_objects3D.h"







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
    Copyright (C) 2021  Sebastien SILVANO - Gabriel SMANIOTTO
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
	
	//shape coordinates
	object->vertices = malloc(sizeof(unit)*object->plaksNbr*3*3);
	if(object->vertices == NULL){
		printf("ERROR -> Malloc vertices is NULL\n");
		free(object->data);
		free(object);
		return NULL;
	}
	
	char*  dataFromBeginingOfPlak = object->data + 84;
	float* dataInFloat;
		
	for(unsigned int n=0; n < object->plaksNbr; n++){
		dataInFloat = (float*)dataFromBeginingOfPlak;
				
		object->vertices[n*9  ] = dataInFloat[ 3];
		object->vertices[n*9+1] = dataInFloat[ 4];
		object->vertices[n*9+2] = dataInFloat[ 5];
		object->vertices[n*9+3] = dataInFloat[ 6];
		object->vertices[n*9+4] = dataInFloat[ 7];
		object->vertices[n*9+5] = dataInFloat[ 8];
		object->vertices[n*9+6] = dataInFloat[ 9];
		object->vertices[n*9+7] = dataInFloat[10];
		object->vertices[n*9+8] = dataInFloat[11];
		//printf("coord : %f %f %f %f %f %f %f %f %f\n", dataInFloat[ 3], dataInFloat[ 4], dataInFloat[ 5], dataInFloat[ 6], dataInFloat[ 7], dataInFloat[ 8], dataInFloat[ 9], dataInFloat[10], dataInFloat[ 11]);

		//translate following pointer (50 bytes per plak)
		dataFromBeginingOfPlak += 50;
	}

	return object;
}

void GLC_freeSTL(stl* object){
	if(!object){
		printf("RUNTIME ERROR > glc_stl.c : GLC_freeSTL() : Object is NULL.\n");
		return;
	}

	//free object
	free(object->data);
	free(object->vertices);
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

	//texture is color & color not null
	if(c != NULL){
		glColor4f(c->r, c->g, c->b, c->a);
	}

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
	
	//shape creation
	GLC_3Dshape(
		object->plaksNbr,
		object->vertices,
		NULL, (char)-1
	);
}
