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
	
	
	return 0;

}

void fb_close()
{
	close(fb_fd);
}


// test   func 1 某一颜色刷背景函数  ok
void fb_draw_back(uint width, uint height, uint color)
{
	int i, j;
	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
		*(fb_pfb + i * width + j) = color;
			}
		}
}


// test
// func2 画线函数，有问题    
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



// 画图片函数 func3  有问题
// 颜色不对，有毛刺
void fb_draw_picture(const unsigned char *pdata)
{
	unsigned int x, y, count;

	for(x = 0; x < WIDTH; x++){
		count = x * HEIGHT;
		for(y = 0; y < HEIGHT; y++){
			count = count + y;
			
			*(fb_pfb + x * WIDTH + y) = ( ((pdata[count]) << 0)  | ((pdata[count + 1]) << 8) | ((pdata[count + 2] ) << 16));
		}
	}
}

// 副本 a ok
// 画图片函数 func3  有问题
// 颜色不对，有毛刺

void fb_draw_picture_a(const unsigned char *pdata)
{
	unsigned int x, y, cnt1 = 0;
	int cnt = -1;

	for(x = 0; x < WIDTH; x++){
		for(y = 0; y < HEIGHT; y++){
			*(fb_pfb + cnt1++) = ( ((pdata[cnt]) << 0)  | ((pdata[cnt + 1]) << 8) | ((pdata[cnt + 2] ) << 16));
			cnt += 3;
		}
	}
}

// 副本 a
// 画图片函数 func3  有问题
// 颜色不对，有毛刺 ok
// 进一步优化 使用指针变量本身自加

void fb_draw_picture_b(const unsigned char *pdata)
{
	unsigned int x, y;
	int cnt = -1;

	for(x = 0; x < WIDTH; x++){
		for(y = 0; y < HEIGHT; y++){
			*(fb_pfb++) = ( ((pdata[cnt]) << 0)  | ((pdata[cnt + 1]) << 8) | ((pdata[cnt + 2] ) << 16));
			cnt += 3;
		}
	}
}


// 画图片函数 func3 ok
// 无彩色版本
// 原因 
	//*(fb_pfb + x * WIDTH + y) = ( ((pdata[cnt++]) << 0)  | ((pdata[cnt++]) << 8) | ((pdata[cnt++] ) << 16));
void fb_draw_picture1(const unsigned char *pdata)
{
	int x, y;
	long cnt = 0;
	for(x = 0; x < HEIGHT; x++){
		for(y = 0; y < WIDTH; y++){
		*(fb_pfb + x * WIDTH + y) = ( ((pdata[cnt]) << 0)  | ((pdata[cnt + 1]) << 8) | ((pdata[cnt + 2] ) << 16));
		cnt += 3;
			}
		}
	printf("fb_draw_picture1: complite.\n");
}


// 画图片函数 func3 ok
void fb_draw_picture1_1(const unsigned char *pdata)
{
	int x, y;
	long cnt = 0;
	for(x = 0; x < WIDTH; x++){
		printf("%d\n", x);
		
		for(y = 0; y < HEIGHT; y++){
		*(fb_pfb + x * HEIGHT + y) = ( ((pdata[cnt]) << 0)  | ((pdata[cnt]) << 8) | ((pdata[cnt] ) << 16));
		
		cnt += 3;
			}
		}
	printf("fb_draw_picture1: complite.\n");
}




 
/*
*
// 画图篇函数test fun4 
// test 小图片显示  
// ok/

height 图片长，width 图片宽；pdata 图片数组指针



*/

void fb_draw_picture_small(const unsigned char *pdata, const unsigned int height, const unsigned int width)
{
	int x, y;
	long cnt = 0;
	for(x = 0; x < width; x++){
		for(y = 0; y < height; y++){
			
		if((x < width) && (y < height)){ 
		*(fb_pfb + x * HEIGHT + y) = ( ((pdata[cnt]) << 0) | ((pdata[cnt + 1]) << 8) | ((pdata[cnt + 2] ) << 16));
		cnt += 3;
		}
		
		
			}
		}
	printf( "fb_draw_picture_small: complite.\n" );
}

// 画图篇函数test fun5
// test 大图片显示
// 待完成，考虑，图片大小

void fb_draw_picture_greath(const unsigned char *pdata)
{
	int x, y;
	int height = 370;
	long cnt = 0;
	for(x = 0; x < WIDTH; x++){
		cnt = x * height;
		
		for(y = 0; y < HEIGHT; y++){
			
		*(fb_pfb + x * HEIGHT + y) = ( ((pdata[cnt]) << 0) | ((pdata[1 + cnt]) << 8) | ((pdata[2 + cnt] ) << 16));
		cnt += 3;
		}
	}
	printf( "fb_draw_picture_greath: complite.\n" );
}



// 画图篇函数test fun6 任意起点 显示
// 函数来源 test fun4
// test 小图片显示  在屏幕中间
// ok

void fb_draw_picture_small_anywhere(const unsigned int height_x, const unsigned int width_y, const unsigned char *pdata)
{
	int x, y;
	int cur_images_height_x = 370, cur_images_width_y = 255;
	int  cnt2_image = 0;//cnt1_fb = 0,
	int x_max, y_max;

//    对越界进行屏蔽
	x_max = height_x + cur_images_height_x;
	y_max = width_y + cur_images_width_y;
	
	if(x_max > HEIGHT )  x_max = HEIGHT;
	if(y_max > WIDTH) y_max = WIDTH;

	for(x = height_x ; x < x_max; x++){
		cnt2_image = (x - width_y) * cur_images_height_x;
		for(y = width_y; y < y_max; y++){
			

		*(fb_pfb + x * HEIGHT + y) = ( ((pdata[cnt2_image]) << 0) | ((pdata[1 + cnt2_image]) << 8) | ((pdata[2 + cnt2_image] ) << 16));
		cnt2_image += 3;
		}
		
		
	}
	printf( "fb_draw_picture_small_anywhere: complite.\n" );
}

