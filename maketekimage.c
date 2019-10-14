/*
 * maketekimage.c
 * 
 * Copyright 2019  rricharz
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include "image.h"

#define xmax 1024
#define ymax  780

int x,y,xs,ys,xstart,ystart,xscale,yscale,pixel[3];
long count;
char *data;

void startplotpoint()
{
    putchar(27);
    putchar(28);
}

void stopplotpoint()
{
    printf("\n");
}

void draw(int x2,int y2)
{
    int hxchange, lychange;

    if ((y2 >> 5) != (ys >> 5)) {       /* if high y has changed */
	putchar((y2 >> 5) + 32);
	count++;
    }
    hxchange = (x2 >> 5) != (xs >> 5);
    lychange = (y2 & 31) != (ys & 31);
    if (hxchange || lychange) {
	putchar((y2 & 31) + 96);
	count++;
    }
    if (hxchange) {                                    /* if high order x has changed */
    	putchar((x2 >> 5) + 32);
	count++;
    }
    putchar((x2 & 31) + 64);
    count++;
    xs = x2;
    ys = y2;
}

void plotpoint(int x,int y,double intensity)
{
    int intensity1;
    if (intensity == 0) intensity1 = 64;
    else if (intensity <= 1) intensity1 = 70;
    else if (intensity <= 2) intensity1 = 75;
    else if (intensity <= 3) intensity1 = 79;
    else if (intensity <= 4) intensity1 = 82;
    else if (intensity <= 5) intensity1 = 85;
    else if (intensity <= 6) intensity1 = 87;
    else if (intensity <= 7) intensity1 = 88;
    else if (intensity <= 8) intensity1 = 89;
    else if (intensity <= 9) intensity1 = 90;
    else if (intensity <= 10) intensity1 = 91;
    else if (intensity <= 11) intensity1 = 92;
    else if (intensity <= 12) intensity1 = 94;
    else if (intensity <= 13) intensity1 = 95;
    else if (intensity <= 14) intensity1 = 96;
    else if (intensity <= 16) intensity1 = 97;
    else if (intensity <= 17) intensity1 = 98;
    else if (intensity <= 19) intensity1 = 99;
    else if (intensity <= 20) intensity1 = 100;
    else if (intensity <= 22) intensity1 = 101;
    else if (intensity <= 23) intensity1 = 102;
    else if (intensity <= 25) intensity1 = 103;
    else if (intensity <= 28) intensity1 = 104;
    else if (intensity <= 31) intensity1 = 105;
    else if (intensity <= 34) intensity1 = 106;
    else if (intensity <= 38) intensity1 = 107;
    else if (intensity <= 41) intensity1 = 108;
    else if (intensity <= 44) intensity1 = 109;
    else if (intensity <= 47) intensity1 = 110;
    else if (intensity <= 50) intensity1 = 111;
    else if (intensity <= 56) intensity1 = 112;
    else if (intensity <= 62) intensity1 = 113;
    else if (intensity <= 69) intensity1 = 114;
    else if (intensity <= 75) intensity1 = 115;
    else if (intensity <= 81) intensity1 = 116;
    else if (intensity <= 88) intensity1 = 117;
    else if (intensity <= 94) intensity1 = 118;
    else intensity1 = 119;
    putchar(intensity1); count++;
    draw(x,y);
}

int main(int argc, char **argv)
{
        double value, imax, imin;
    
	if ((width>xmax) || (height>ymax)) {
	    printf("Image too large\n");
	    exit (1);
	}
	
	xscale = xmax / width;
	yscale = ymax / height;
	
	if (yscale>xscale) yscale = xscale;
	else if (xscale>yscale) xscale = yscale;
	
	xstart = (xmax - xscale*width) / 2;
	ystart = (ymax - yscale*height) / 2;
	
	// normalize
	
	data = header_data;
	imax = 0.0;
	imin = 100.0;
	
	for (int i = 1; i < height * width; i++) {
	   HEADER_PIXEL(data,pixel);
	   value = (double)(pixel[0]+pixel[1]+pixel[2])/7.68;
	   if (imax < value) imax = value;
	   if (imin > value) imin = value;
	}
	
	// convert the data
	
	data = header_data;
	xs = 0;
	ys = 0;
	count = 0;
	for (y=ystart+height*yscale; y>ystart; y-=yscale) {
	    startplotpoint();
	    
	    for (x=xstart; x<xstart+width*xscale; x+=xscale) {
		HEADER_PIXEL(data,pixel);
		value = (double)(pixel[0]+pixel[1]+pixel[2])/7.68;
		value = imin + value * 100.0 / (imax - imin);
		plotpoint(x,y,value);		
	    }
	    
	    stopplotpoint();	    
	}
	
	// print information about data
	
	fprintf(stderr, "imax=%d, imin=%d\n",(int)imax,(int)imin);
	fprintf(stderr, "resolution=%dx%d\n",width,height);
	fprintf(stderr, "bytes per pixel=%f\n",(double)count/(width*height));

	
	return 0;
}

