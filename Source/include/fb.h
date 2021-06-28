

#ifndef __FB_H_
#define __FB_H_


#define FBDEVICE "/dev/fb0"


#define HEIGHT 1024
#define WIDTH 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_RED 0x00ff0000
#define COLOR_BLUE 0x000000ff
#define COLOR_GREEN 0xff00ff00
#define COLOR_REDP 0x00ff0000
#define COLOR_BLUEP 0x000000ff 
#define COLOR_GREENP 0xff00ff00

typedef unsigned int uint;
typedef unsigned char uchar;


int fb_open();
void fb_close();
void fb_draw_back(uint width, uint height, uint color);
void fb_draw_line(int begin_x, int begin_y, int end_x, int end_y, uint color);







#endif
