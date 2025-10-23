#ifndef GLC_SPECIALS_H
#define GLC_SPECIALS_H






// ---------------- IMPORTATIONS ----------------

//glc
#include "glc.h"






// ---------------- TYPES ----------------

//pictures
typedef struct {
	unsigned int width;
	unsigned int height;
	color* data;
} pict;






// ---------------- 2D ELEMENTS ----------------

//text
void GLC_text(char* text, unit size, unit x, unit y);

#endif
