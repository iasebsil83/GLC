#ifndef GLC_OBJECTS2D_H
#define GLC_OBJECTS2D_H








// ---------------- IMPORTATIONS ----------------

//glc
#include "glc.h"








// ---------------- 2D UTILITIES ----------------

//forms
void GLC_2DPoint(
	unit x, unit y,
	color* c
);
void GLC_2DLine(
	unit x1, unit y1,
	unit x2, unit y2,
	color* c
);
void GLC_2DTriangle(
	unit x1, unit y1,
	unit x2, unit y2,
	unit x3, unit y3,
	color* c, char filled
);
void GLC_2DRectangle(
	unit x1, unit y1,
	unit x2, unit y2,
	color* c, char filled
);
void GLC_2DQuad(
	unit x1, unit y1,
	unit x2, unit y2,
	unit x3, unit y3,
	unit x4, unit y4,
	color* c, char filled
);

void GLC_2DCircle(
	unit x, unit y,
	unit radius, unsigned int divisions,
	color* c, char filled
);








#endif
