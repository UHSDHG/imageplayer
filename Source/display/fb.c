/*
*fb 基础代码来自之前写的课堂代码
*
*
*/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fb.h>









struct fb_fix_screeninfo fb_fscreeninfo;
struct fb_var_screeninfo fb_get_vscreeninfo;
int *fb_pfb = NULL;
int fb_fd = -1, ret = -1;




int fb_open()
{
	fb_fd = open(FBDEVICE, O_RDWR);
	if(fb_fd < 0)
	{
		perror("open");
		return -1;
	}

	printf("open %s device success!\n", FBDEVICE);
	
	// 第二步：获取设备的硬件信息
	ret = ioctl(fb_fd,FBIOGET_FSCREENINFO, &fb_fscreeninfo);
	if(ret < 0)
	{
                perror("get_fixed_fbscreeninfo.\n");
                return -1;
	}
	printf("open %s device var fbinfo success!\n", FBDEVICE);

	// 第三步：地址映射
	fb_pfb = (int *)mmap(NULL, fb_fscreeninfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
	if(NULL == fb_pfb){
		perror("mmap");
	}
	
	printf("blue\n");
	fb_draw_back(WIDTH, HEIGHT, COLOR_BLUE);
	
	return 0;

}

void fb_close()
{
	close(fb_fd);
}

void fb_draw_back(uint width, uint height, uint color)
{
	int i, j;
	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
		*(fb_pfb + i * width + j) = color;
			}
		}
}


void fb_draw_line(int begin_x, int begin_y, int end_x, int end_y, uint color)
{
	int i, b;
	float k;
	k = (end_y - begin_y) / ((float)end_x - begin_x);
	b = begin_y - (begin_x * k);
	printf("fb_draw_line: (%d,%d) (%d,%d).\n", begin_x, begin_y, end_x, end_y);
	sleep(1);
	for(i = begin_x; i < end_x; i++){
		
		*(fb_pfb + (unsigned int)(i * HEIGHT * 0.5) + i) = color;
		}
}
