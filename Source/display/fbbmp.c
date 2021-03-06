
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "fb.h"
#include "config.h"









/*
*函数名：is_bmp 
*函数功能：判断是否为 bmp图片,获取文件头信息，并填充pdata
*
*参数：bmp_picinfo *pdata 是一个封装bmp信息的结构体指针
*返回值：-1 表示不是bmp ， 0表示是bmp
*/

int is_bmp(const char *pathname){

		int ret = 0;
		int fd = 0;
		BITMAPFILEHEADER bmp_bitmaphead;
/*
		getwd(pwd_cur);
		printf("%s\n", pwd_cur);
*/
		// 第一步打开文件，得到文件id
		
		if(-1 == (fd = open(pathname , O_RDWR)))
		{
			debug("%s open failed.\n", pathname);
			return -1;
		}
		debug("open %s file success!\n", pathname);

		
		// 第二步：获取文件头信息
		if(-1 == read(fd, &bmp_bitmaphead, sizeof(BITMAPFILEHEADER))){
			
		debug("read\n");
		ret = -1;
		goto my_close_do;

	}
		debug("read %s  success of BITMAPFILEHEADER size!\n", pathname);


	// 第三步：判断是否为bmp文件
	//0x4d42 对应的是char BM 
	if(0x4d42 != bmp_bitmaphead.bfType){
		debug("not is bmp file\n");
		ret = -1;
		goto my_close_do;
	}
	/*
	// 填充pdata结构体

	debug("the %s is bmp file\n", pic_data->pathname);*/
	debug("16 read bfType =  %x \n", bmp_bitmaphead.bfType);
	debug("32 read bfSize = %x \n", bmp_bitmaphead.bfSize);
	debug("16 read bfReserved1 = %x \n", bmp_bitmaphead.bfReserved1);
	debug("16 read bfReserved2 = %x \n", bmp_bitmaphead.bfReserved2);
	debug("32 read bfOffBits = %x \n", bmp_bitmaphead.bfOffBits);

	//return ret;

my_close_do:
	close(fd);
	debug("close fd ok.\n");
	return ret;
}






/*
*函数名：analysis_bmp
*函数功能：解析bmp图片，并使用fb_draw显示图片
*
*参数：const char * pdata分析的文件pathname
*返回值：无
*/

void display_bmp(const      char * pdata){

	// 第一步：实例化pic_data图片数据结构体 , pathname 给pic_data填充
	bmp_picinfo *pic_data = NULL;
	BITMAPFILEHEADER *bmp_bitmaphead = NULL;
	
	
	pic_data = (bmp_picinfo *)malloc(sizeof(bmp_picinfo)); // display_bmp本函数末尾释放
	pic_data->pathname = pdata;

	bmp_bitmaphead = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));// display_bmp本函数末尾释放

	

	// 第二步：判断是否为bmp文件
	if(0 != is_bmp(pic_data->pathname)){
		debug("not bmp file\n");//不是bmp
		goto my_end;
	}
	
	debug("%s is bmp file\n", pic_data->pathname);//不是bmp
		

	// 打开文件，读取文件头，读取信息头
	


	// 打开文件
	pic_data->fd = 0;
	if(0 >= (pic_data->fd = open(pic_data->pathname, O_RDWR))){
	debug("%s open failed, pic_data->fd = %d.\n", pic_data->pathname, pic_data->fd);
	goto my_end;

	}
	debug("%s open success, pic_data->fd = %d.\n", pic_data->pathname, pic_data->fd);
			
	// 读取文件头
	if(-1 == read(pic_data->fd, bmp_bitmaphead, sizeof(BITMAPFILEHEADER))){
			
		debug("read bmp_bitmaphead failed\n");
		goto my_close_fd;

	}
	debug("read bmp_bitmaphead success\n");


	// 文件头赋值
	
	pic_data->bfType = bmp_bitmaphead->bfType;
	pic_data->bfSize = bmp_bitmaphead->bfSize;
	pic_data->bfOffBits = bmp_bitmaphead->bfOffBits;
		debug("123\n");

	// 实例化信息头结构体，并获取信息头
	BITMAPINFODEADER *bmp_bitmapinfo = (BITMAPINFODEADER*) \
	malloc(sizeof(BITMAPINFODEADER)); // 在本函数display_bmp函数末尾释放


	
	if(-1 == read(pic_data->fd, bmp_bitmapinfo, sizeof(BITMAPINFODEADER))){
		debug("bmp_bitmapinfo read failed\n");
		goto my_close_fd;
	}
	debug("bmp_bitmapinfo read success\n");
	
	// 填充结构体，并调试输出
	pic_data->biWidth =  bmp_bitmapinfo->biWidth;
	pic_data->biHeight = bmp_bitmapinfo->biHeight;
	pic_data->biBitCount = bmp_bitmapinfo->biBitCount;
	pic_data->biCompression = bmp_bitmapinfo->biCompression;
	pic_data->biSizeImage = bmp_bitmapinfo->biSizeImage;
	debug("----------bmp_bitmapinfo-----------------\n");
	debug("32 read biSize =  %x \n", bmp_bitmapinfo->biSize);
	debug("32 read biWidth = %x \n", bmp_bitmapinfo->biWidth);
	debug("32 read biHeight = %x \n", bmp_bitmapinfo->biHeight);
	debug("16 read biPlanes = %x \n", bmp_bitmapinfo->biPlanes);
	debug("16 read biBitCount = %x \n", bmp_bitmapinfo->biBitCount);
	debug("32 read biCompression = %x \n", bmp_bitmapinfo->biCompression);
	debug("32 read biSizeImage =  %x \n", bmp_bitmapinfo->biSizeImage);
	debug("32 read biXPelsPerMeter = %x \n", bmp_bitmapinfo->biXPelsPerMeter);
	debug("32 read biYPelsPerMeter = %x \n", bmp_bitmapinfo->biYPelsPerMeter);
	debug("32 read biClrUsed = %x \n", bmp_bitmapinfo->biClrUsed);
	debug("32 read biClrImportant = %x \n", bmp_bitmapinfo->biClrImportant);

	// 申请pdata的图片数据空间
 	pic_data->pic_data = (char *)malloc(sizeof(char)*pic_data->biWidth * pic_data->biHeight * 3);// 在本函数display_bmp函数末尾释放
	// 重置文件指针位置到图片数据处
	lseek(pic_data->fd, pic_data->bfOffBits, SEEK_SET);
	// 读取图片数据
	if(-1 == read(pic_data->fd, pic_data->pic_data, pic_data->biWidth * pic_data->biHeight * 3)){
		debug("READ error\n");
		goto my_close_fd;

	}
	debug("READ success\n");


	// 画图
	debug("------------draw picture of bmp------------\n");
	// 打开fb设备
	fb_open();
	// 调用函数画图
	fb_draw_picture_end1(pic_data);
	
	debug("fb_draw_picture_end1 ok\n");

my_close_fd:
	close(pic_data->fd);	
my_end:
	free(bmp_bitmapinfo);
	free(pic_data->pic_data);
	free(pic_data);
	free(bmp_bitmaphead);
	debug("free ok.\n");
}






