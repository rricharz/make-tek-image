all: maketekimage
maketekimage: maketekimage.c image.h
	gcc -o maketekimage maketekimage.c

