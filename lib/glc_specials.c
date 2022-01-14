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
