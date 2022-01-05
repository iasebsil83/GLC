#ifndef GLC_OBJECTS3D_H
#define GLC_OBJECTS3D_H








// ---------------- IMPORTATIONS ----------------

//glc
#include "glc.h"








// ---------------- 3D OBJECTS ----------------

//shapes
void GLC_3DHexaedron(
	unit px, unit py, unit pz,
	unit rx, unit ry, unit rz,
	unit lx, unit ly, unit lz,
	color* c
);

#define GLC_3DCube( \
	px, py, pz,      \
	rx, ry, rz,      \
	l,  c            \
)                    \
GLC_3DHexaedron(px,py,pz, rx,ry,rz, l,l,l, c)

void GLC_3DSphere(
	unit px, unit py, unit pz,
	unit radius, unsigned int divisions,
	color* c
);








#endif
