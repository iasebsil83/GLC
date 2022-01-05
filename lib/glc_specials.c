// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//own header
#include "glc_specials.h"








// ---------------- 2D ELEMENTS ----------------

//text
void GLC_text(char* text, unit size, unit x, unit y){

	//moving over display (use of the 3rd dimension)
	glPushMatrix();
	glTranslatef(x,y,0);
	glScalef(size,size,size);

	//error case
	if(text == NULL){
		printf("RUNTIME ERROR > glc_specials.c : GLC_text() : Text is NULL.\n");
		return;
	}

	//write text character per character
	while(*text){
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *text++);
	}
	glPopMatrix();
}



//images
void GLC_image(unit x, unit y, unit width, unit height, color* data){
	glRasterPos2i(x,y);
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);
}
