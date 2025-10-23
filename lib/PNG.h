#ifndef ________PNG_H
#define ________PNG_H






// ---------------- IMPORTATIONS ----------------

//structure
typedef struct{
	int width, height;
	int* data;
} PNG;






// ---------------- BASICS ----------------

//read - write
PNG* png_read(char* fileName);
char png_write(PNG* image, char* fileName);

#endif
