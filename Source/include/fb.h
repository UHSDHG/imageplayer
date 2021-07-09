

#ifndef __FB_H_
#define __FB_H_

#include "images.h"
#include "fbbmp.h"

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

// À¢±≥æ∞
void fb_draw_back(uint width, uint height, uint color);
// ª≠œﬂ
void fb_draw_line(int begin_x, int begin_y, int end_x, int end_y, uint color);
// œ‘ æÕº∆¨
void fb_draw_picture(const unsigned char *pdata);
void fb_draw_picture_end1(bmp_picinfo *pic_data);

void fb_draw_picture_a(const unsigned char *pdata);
void fb_draw_picture_b(const unsigned char *pdata);

void fb_draw_picture1(const unsigned char *pdata);
void fb_draw_picture1_1(const unsigned char *pdata);

//  –°Õº∆¨œ‘ æ
void fb_draw_picture_small(const         char *pdata, \
const unsigned int height, const unsigned int width);

void fb_draw_picture_small_endt0begin(const char *pdata, const unsigned int height, \
	const unsigned int width);


void fb_draw_picture_greath(const unsigned char *pdata);

 
void fb_draw_picture_small_anywhere(const unsigned int height_x,  \
	const unsigned int width_y, const unsigned char *pdata);











#endif
