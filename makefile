run: main.o files.o PNG.o glc.o glc_specials.o glc_objects2D.o glc_objects3D.o glc_stl.o
	gcc -o run -Wall -O2 main.o files.o PNG.o glc.o glc_specials.o glc_objects2D.o glc_objects3D.o glc_stl.o -lpng -lm -lGL -lGLU -lglut 
	rm -f *.o

main.o: src/main.c src/main.h lib/glc.h
	gcc -c -Wall -O2 src/main.c -I/usr/include/GL 

files.o: lib/files.c lib/files.h
	gcc -c -Wall -O2 lib/files.c  

PNG.o: lib/PNG.c lib/PNG.h
	gcc -c -Wall -O2 lib/PNG.c  

glc.o: lib/glc.c lib/glc.h
	gcc -c -Wall -O2 lib/glc.c -I/usr/include/GL 

glc_specials.o: lib/glc_specials.c lib/glc_specials.h lib/glc.h
	gcc -c -Wall -O2 lib/glc_specials.c -I/usr/include/GL 

glc_objects2D.o: lib/glc_objects2D.c lib/glc_objects2D.h lib/glc.h lib/PNG.h
	gcc -c -Wall -O2 lib/glc_objects2D.c -I/usr/include/GL -lm 

glc_objects3D.o: lib/glc_objects3D.c lib/glc_objects3D.h lib/glc.h lib/PNG.h
	gcc -c -Wall -O2 lib/glc_objects3D.c -I/usr/include/GL -lm 

glc_stl.o: lib/glc_stl.c lib/glc_stl.h lib/glc.h lib/glc_objects3D.h lib/files.h
	gcc -c -Wall -O2 lib/glc_stl.c -I/usr/include/GL -lm 

