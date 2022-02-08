#ifndef GLC_STL_H
#define GLC_STL_H








// ---------------- IMPORTATIONS ----------------

//glc
#include "glc.h"








// ---------------- DEFINITIONS ----------------

//stl data
typedef struct {
	unsigned int plaksNbr;
	char*        data;
	unit* vertices;
} stl;








// ---------------- STL ----------------

//object
stl* GLC_loadSTL(char* path);
void GLC_freeSTL(stl* object);

//display
void GLC_3DSTL(
	stl* object,
	unit px, unit py, unit pz, //position
	unit rx, unit ry, unit rz, //rotation
	unit sx, unit sy, unit sz, //scale
	color* c
);








#endif
