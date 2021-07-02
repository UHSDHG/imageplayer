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
	
	// �ڶ�������ȡ�豸��Ӳ����Ϣ
	ret = ioctl(fb_fd,FBIOGET_FSCREENINFO, &fb_fscreeninfo);
	if(ret < 0)
	{
                perror("get_fixed_fbscreeninfo.\n");
                return -1;
	}
	printf("open %s device var fbinfo success!\n", FBDEVICE);

	// ����������ַӳ��
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
	printf("fb_draw_line: (%d,%d) (%d,%d).\n", begin_x, begin_y, end_x, end_y);
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
	int cnt = -1;

	for(x = 0; x < WIDTH; x++){
		for(y = 0; y < HEIGHT; y++){
			*(fb_pfb++) = ( ((pdata[cnt]) << 0)  | ((pdata[cnt + 1]) << 8) | ((pdata[cnt + 2] ) << 16));
			cnt += 3;
		}
	}
}


// ��ͼƬ���� func3 ok
// �޲�ɫ�汾
// ԭ�� 
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


// ��ͼƬ���� func3 ok
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
// ��ͼƪ����test fun4 
// test СͼƬ��ʾ  
// ok/

height ͼƬ����width ͼƬ��pdata ͼƬ����ָ��



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

// ��ͼƪ����test fun5
// test ��ͼƬ��ʾ
// ����ɣ����ǣ�ͼƬ��С

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



// ��ͼƪ����test fun6 ������� ��ʾ
// ������Դ test fun4
// test СͼƬ��ʾ  ����Ļ�м�
// ok

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

	for(x = height_x ; x < x_max; x++){
		cnt2_image = (x - width_y) * cur_images_height_x;
		for(y = width_y; y < y_max; y++){
			

		*(fb_pfb + x * HEIGHT + y) = ( ((pdata[cnt2_image]) << 0) | ((pdata[1 + cnt2_image]) << 8) | ((pdata[2 + cnt2_image] ) << 16));
		cnt2_image += 3;
		}
		
		
	}
	printf( "fb_draw_picture_small_anywhere: complite.\n" );
}

