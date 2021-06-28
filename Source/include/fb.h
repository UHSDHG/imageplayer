
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>




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
int *fb_pfb = NULL;
int fb_fd = -1, ret = -1;


struct fb_fix_screeninfo fb_fscreeninfo = {0};
struct fb_var_screeninfo fb_get_vscreeninfo = {0};

int fb_open();
void fb_close();

void fb_draw_back(uint width, uint height, uint color, int *pfb);































s















