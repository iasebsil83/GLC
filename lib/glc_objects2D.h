#ifndef GLC_OBJECTS2D_H
#define GLC_OBJECTS2D_H








// ---------------- IMPORTATIONS ----------------

//glc
#include "glc.h"

//pictures
#include "PNG.h"








// ---------------- 2D UTILITIES ----------------

//forms
void GLC_2DPoint(
	unit x, unit y,
	color* c
);

void GLC_2DLine(
	unit x1, unit y1, //1st point
	unit x2, unit y2, //2nd point
	color* c
);

void GLC_2DTriangle(
	unit x1, unit y1,     //1st point
	unit x2, unit y2,     //2nd point
	unit x3, unit y3,     //3rd point
	color* c, char filled
);

void GLC_2DRectangle(
	unit x1, unit y1,      //first corner
	unit x2, unit y2,      //second corner
	void* c, char texType, //texture
	char filled
);

void GLC_2DQuad(
	unit x1, unit y1,        //1st corner
	unit x2, unit y2,        //2nd corner
	unit x3, unit y3,        //3rd corner
	unit x4, unit y4,        //4th corner
	void* tex, char texType, //texture
	char filled
);

void GLC_2DCircle(
	unit radius, unsigned int divisions, //circle attributes
	unit x, unit y,                      //center position
	color* c, char filled
);








#endif
