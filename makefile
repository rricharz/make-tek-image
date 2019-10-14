all: maketekimage
maketekimage: maketekimage.c maketekimage.h image.h
	gcc -o maketekimage maketekimage.c

