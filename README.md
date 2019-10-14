# make-tek-image
This is a very small and simple conversion tool to create a Tektronix
4014 special point plot file (grayscale) from a picture. It uses the
intensity table as described in the Tektronix 4014 manual Fig. F-3
on page F-8, and the corresponding table F-6 on page F-9, with
intensity values between 64 (corresponding to 0%) and 119
(corresponding to 100%). This is the grayscale intensity table
implemented in tek4010.

![screen_shot](spock.png?raw=true "tek4010 screendump")

The program is not very convenient to use, but it works.

To use this program on a Raspberri Pi or another Linux system,
proceed as follows:

1. Put your image in this folder with the program source
   maketekimage.c and makefile.

2. Open your image with the gnu image manipulation program GIMP.

3. Use the menu Image->Scale Image... and reduce the image size
   to something acceptable given the slow Tektronix 4010 grayscale
   image display capabilities.
   
   I propose Height not larger than 380 and Width not larger than
   512. In this case the conversion tool will make each pixel
   the size of 2x2 tekpoints.

   Use the "Scale" button to scale the image to that size.

   It is possible to make higher resolution images, but the
   display of these images on a Tektronix 4014 or tek4010 will
   be extremely slow.

4. Export the image as a C source code header file with the menu
   File->Export...
   Click Select File Type (By Extension) at the bottom of the
   popup window and select "C source code header     h".
   Overwrite the name at the top of the window with "image.h".
   Use the "Export" button to export the file.

5. Open a Terminal Window in this folder and type
   "make". This will compile the program with image.h you made
   before.
   Then execute the command "./maketekimage >image.plt"
   This will create the image.plt file of your image

6. If you have installed [tek4010](https://github.com/rricharz/Tek4010)
   you can now display your Tektronix 4014 grayscale image with
   "tek4010 -noexit -b100000 cat image.plt". Be patient. This is state
   of the art 1970's grayscale image display at speed the
   Tektronix 4014 was able to handle.
