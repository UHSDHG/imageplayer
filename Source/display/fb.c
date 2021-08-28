/*
*fb ������������֮ǰд�Ŀ��ô���
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
#include <fbjpeg.h>

#include "config.h"



typedef int (*fb_pfbp)[1024];


struct fb_fix_screeninfo fb_fscreeninfo;
struct fb_var_screeninfo fb_get_vscreeninfo;
fb_pfbp my_fb_pfb = (fb_pfbp)NULL;
int *fb_pfb = NULL;
int fb_fd = -1, ret = -1;

int fb_open_add1()
{
	
	fb_fd = open(FBDEVICE, O_RDWR);
	if(fb_fd < 0)
	{
		debug("open\n");
		return -1;
	}

	debug("open %s device success!\n", FBDEVICE);
	
	// �ڶ�������ȡ�豸��Ӳ����Ϣ
	ret = ioctl(fb_fd,FBIOGET_FSCREENINFO, &fb_fscreeninfo);
	if(ret < 0)
	{
                debug("get_fixed_fbscreeninfo.\n");
                return -1;
	}
	debug("open %s device var fbinfo success!\n", FBDEVICE);

	// ����������ַӳ��
	my_fb_pfb = (fb_pfbp)mmap(NULL, fb_fscreeninfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
	if(NULL == my_fb_pfb){
		debug("mmap");
	}
	
	
	return 0;

}


int fb_open()
{
	debug("i am here.\n");
	fb_fd = open(FBDEVICE, O_RDWR);
	if(fb_fd < 0)
	{
		debug("open\n");
		return -1;
	}

	debug("open %s device success!\n", FBDEVICE);
	
	// �ڶ�������ȡ�豸��Ӳ����Ϣ
	ret = ioctl(fb_fd,FBIOGET_FSCREENINFO, &fb_fscreeninfo);
	if(ret < 0)
	{
                debug("get_fixed_fbscreeninfo.\n");
                return -1;
	}
	debug("open %s device var fbinfo success!\n", FBDEVICE);

	// ����������ַӳ��
	fb_pfb = (int *)mmap(NULL, fb_fscreeninfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
	if(NULL == fb_pfb){
		debug("mmap");
	}
	
	
	return 0;

}

void fb_close()
{
	close(fb_fd);
}


// test   func 1 ĳһ��ɫˢ��������  ok
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
// func2 ���ߺ�����������    
void fb_draw_line(int begin_x, int begin_y, int end_x, int end_y, uint color)
{
	int i, b;
	float k;
	k = (end_y - begin_y) / ((float)end_x - begin_x);
	b = begin_y - (begin_x * k);
	debug("fb_draw_line: (%d,%d) (%d,%d).\n", begin_x, begin_y, end_x, end_y);
	sleep(1);
	for(i = begin_x; i < end_x; i++){
		
		*(fb_pfb + (unsigned int)(i * HEIGHT * 0.5) + i) = color;
		}
}



// ��ͼƬ���� func3  ������
// ��ɫ���ԣ���ë��
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

/*
*��������analysis_bmp
*�������ܣ�����bmpͼƬ����ʹ��fb_draw��ʾͼƬ
*
*������const char * pdata�������ļ�pathname
*����ֵ����
*/

void fb_draw_picture_end1(bmp_picinfo *pic_data)
{
	int x, y, count = 0;
	
	debug("pictureis:%s\n", pic_data->pathname);

	for(y = pic_data->biHeight - 1; y >= 0; y--){
		
		for(x = 0; x < pic_data->biWidth; x++){
			*(fb_pfb + y * HEIGHT + x)  = ( ((pic_data->pic_data[count + 0]) << 0)  |  ((pic_data->pic_data[count + 1]) << 8) | ((pic_data->pic_data[count + 2] ) << 16));
			count += 3;
		}
	}
}



// ���� a ok
// ��ͼƬ���� func3  ������
// ��ɫ���ԣ���ë��

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

// ���� a
// ��ͼƬ���� func3  ������
// ��ɫ���ԣ���ë�� ok
// ��һ���Ż� ʹ��ָ����������Լ�

void fb_draw_picture_b(const unsigned char *pdata)
{
	unsigned int x, y;
	int cnt = 0;

	for(x = 0; x < WIDTH; x++){
		for(y = 0; y < HEIGHT; y++){
			*(fb_pfb + x * HEIGHT + y) = ( ((pdata[cnt]) << 0)  | ((pdata[cnt + 1]) << 8) | ((pdata[cnt + 2] ) << 16));
			cnt += 3;
		}
	}
}

/*
*�������� fb_draw_picture1_1
*���ܣ� ͼƬ������Ļ������»�ͼƬ���޲�ɫ�汾
*������ ͼƬ����ָ�� pdata
*
*����ֵ: -
*
* ���״����ok
* ��ʷ��Դ��-
*ԭ��*(fb_pfb + x * WIDTH + y) = ( ((pdata[cnt++]) << 0)  | ((pdata[cnt++]) << 8) | ((pdata[cnt++] ) << 16));

*/

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
	debug("fb_draw_picture1: complite.\n");
}


/*
*�������� fb_draw_picture1_1
*���ܣ� ͼƬ������Ļ������»�ͼƬ
*������ ͼƬ����ָ�� pdata
*
*����ֵ: -
*
* ���״����ok
* ��ʷ��Դ��-
*/

void fb_draw_picture1_1(const unsigned char *pdata)
{
	int x, y;
	long cnt = 0;
	for(x = 0; x < WIDTH; x++){
		debug("%d\n", x);
		
		for(y = 0; y < HEIGHT; y++){
		*(fb_pfb + x * HEIGHT + y) = ( ((pdata[cnt]) << 0)  | ((pdata[cnt]) << 8) | ((pdata[cnt] ) << 16));
		
		cnt += 3;
			}
		}
	debug("fb_draw_picture1: complite.\n");
}




/*
*��������fb_draw_picture_small
*���ܣ� ͼƬС����Ļ������»�ͼƬ
*������ ͼƬ����ָ�� pdata�� height��width ͼƬ�ĸߺͿ�
*
*����ֵ: -
*
* ���״����ok
* ��ʷ��Դ��-
*/

void fb_draw_picture_small(const char *pdata, const unsigned int height, const unsigned int width)
{
	int x =0, y = 0;
	long cnt = 0;
	for(y = 0; y < height; y++){
		debug( "fb_draw_picture_small: complite line %d.\n" , x);
		for(x = 0; x < width; x++){
			
		if((x < width) && (y < height)){ 
		*(fb_pfb + y * HEIGHT + x) = ( ((pdata[cnt]) << 16) | ((pdata[cnt + 1]) << 8) | ((pdata[cnt + 2] ) << 0));
		cnt += 3;
		}
		
		
			}
		}
	debug( "fb_draw_picture_small: complite.\n" );
}

/*
*
// ��ͼƪ����test fun4_1
// test СͼƬ��ʾ  
// ok/

height ͼƬ�ߣ�width ͼƬ��pdata ͼƬ����ָ��



*/

void fb_draw_picture_small_endt0begin(const char *pdata, const unsigned int height, const unsigned int width)
{
	int x, y;
//	long cnt = 0;
	for(y = height - 1; y >= 0; y--){
		for(x = width - 1; x >= 0; x--){
			
		if((x >= 0) && (y >= 0)){ 
		*(fb_pfb + y * HEIGHT + x) =  ((*pdata << 0) | (*(pdata + 1)<< 8) | (*(pdata + 2) << 16));
		pdata += 3;

		}
		
		
			}
		}
	debug( "fb_draw_picture_small: complite.\n" );
}

/*
*��������fb_draw_picture_greath
*���ܣ� ͼƬ������Ļ������»�ͼƬ
*������ ͼƬ����ָ�� pdata
*
*����ֵ: ��
*
* ���״����ok
*/


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
	debug( "fb_draw_picture_greath: complite.\n" );
}




/*
*��������fb_draw_picture_small_anywhere
*���ܣ� ��СͼƬ������Ļ����һ���㿪ʼ
*�������� height_x �� width_y , (height_x, width_y) ��ͼƬ��ʾ��������ꣻ ͼƬ����ָ�� pdata
*
*����ֵ: ��
*
* ���״����ok
*/



void fb_draw_picture_small_anywhere(const unsigned int height_x, const unsigned int width_y, const unsigned char *pdata)
{
	int x, y;
	
	int cur_images_height_x = 370, cur_images_width_y = 255;
	int  cnt2_image = 0;//cnt1_fb = 0,
	int x_max, y_max;



//    ��Խ���������
	x_max = height_x + cur_images_height_x;
	y_max = width_y + cur_images_width_y;
	
	if(x_max > HEIGHT )  x_max = HEIGHT;
	if(y_max > WIDTH) y_max = WIDTH;

	for(y = width_y; y < y_max; y++){
		
		cnt2_image = ((y - width_y) * cur_images_height_x * 3);
		
		for(x = height_x ; x < x_max; x++){


		*(fb_pfb + y * HEIGHT + x) = ( ((pdata[cnt2_image]) << 0) | ((pdata[1 + cnt2_image]) << 8) | ((pdata[2 + cnt2_image] ) << 16));
		cnt2_image += 3;
		}
		
		
	}
	debug( "fb_draw_picture_small_anywhere: complite.\n" );
}



/*****************************************************************************************************************
*
*��ʾjpegͼƬ
*****************************************************************************************************************/
void fb_draw_jpeg(jpeg_picinfop pdata){
	
	int i,j;
	int width,height;
	unsigned char *pic = pdata->data;

	debug("pic = %p\n",pic);
	debug("fb_pfb  = %p\n",fb_pfb );
	
	unsigned int cnt = 0;

	
	if(pdata->biWidth <= 1024) width = pdata->biWidth;
	else width = 1024;
	
	if(pdata->biHeight <= 600) height = pdata->biHeight;
	else height = 600;
	
	debug("i am here.\n");
	debug("height  = %d\n",height );
	debug("width  = %d\n",width );

	for(i = 0; i < height; i++){
		//debug("i =%d\n", i);
		cnt = i * pdata->biWidth*3;
		for(j = 0; j < width; j++){
		*(fb_pfb + i * width + j) = ( ((pic[cnt+0]) << 0) | ((pic[cnt+1]) << 8) | ((pic[cnt+2]) << 16));

		cnt+=3;
		}
	}

debug("finish\n");

}
void put_scanline_someplace(unsigned char *buffer,int           row_stride, int line){
#ifndef no_compile
	debug("i am here!\n");
	int i;
	int width;
	int cnt = 0;
	if(row_stride > 1024) width = 1024;
	else width = row_stride;
	debug("row_stride = %d\n", row_stride);
	debug("width = %d\n", width);
	debug("fb_pfb = %p\n", fb_pfb);
	for(i = 0; i < width; i++){
		
		*(fb_pfb + line * width + i) = ( ((buffer[cnt+0]) << 0) | ((buffer[cnt+1]) << 8) | ((buffer[cnt+2]) << 16));
		cnt += 3;
	}
#endif
}

