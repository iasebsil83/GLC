#ifndef GLC_OBJECTS3D_H
#define GLC_OBJECTS3D_H








// ---------------- IMPORTATIONS ----------------

//glc
#include "glc.h"

//pictures
#include "PNG.h"








// ---------------- 3D OBJECTS ----------------

//shapes
void GLC_3DPlane(
	unit lx, unit ly,          //length (width, height)
	unit px, unit py, unit pz, //position
	unit rx, unit ry, unit rz, //rotation
	unit sx, unit sy, unit sz, //scale
	void* tex, char texType    //texture
);

void GLC_3DHexaedron(
	unit lx, unit ly, unit lz, //length (width, height, depth)
	unit px, unit py, unit pz, //position
	unit rx, unit ry, unit rz, //rotation
	unit sx, unit sy, unit sz, //scale
	void* tex, char texType    //texture
);

//same thing as GLC_3DHexaedron() except length is only 1 attribute
#define GLC_3DCube( \
	l,              \
	px, py, pz,     \
	rx, ry, rz,     \
	sx, sy, sz,     \
	tex, texType    \
)                   \
GLC_3DHexaedron(l,l,l, px,py,pz, rx,ry,rz, sx,sy,sz, tex,texType)

void GLC_3DSphere(
	unit radius, unsigned int divisions, //divisions = precision of the sphere
	unit px, unit py, unit pz,           //position
	unit sx, unit sy, unit sz,           //scale
	color* c
);








#endif
