#ifndef __CONFIG_H_
#define __CONFIG_H_


#include <stdio.h>
#include <linux/input.h>s

#include <sys/types.h>
#include "image_manage.h"


//#undef DEBUG //不编译

/*************************************调试宏*****************************************/

#ifdef DEBUG
#define debug(format, ...)   fprintf(stderr,"[debug][%s:%s:%d] "format"",\
               __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else


#define debug(...)
#endif

/*************************************常用配置*****************************************/
#define PNG_BYTES_TO_CHECK 4 


// image_manage
#define image_manage_default_size 1
// 定义系统中的触摸屏设备的设备名
#define DEVICE_KEY "/dev/input/event2"

/**********************************结构体封装******************************************/
//bmp
//下面两个结构是位图的结构  
#pragma pack(1);
// 文件头结构体
typedef struct BITMAPFILEHEADER  
{   
    u_int16_t bfType;   // 文件类型
    u_int32_t bfSize;   // 文件大小
    u_int16_t bfReserved1;    //保留
    u_int16_t bfReserved2;   
    u_int32_t bfOffBits;   // 从文件头到位图数据的偏移量
}BITMAPFILEHEADER;   
#pragma pack();


#pragma pack(1);
typedef struct BITMAPINFOHEADER // 信息头结构体 
{   
    u_int32_t biSize;   //信息头大小
    u_int32_t biWidth;   // 位图的像素宽
    u_int32_t biHeight;   //位图的像素高，如果为正说明图像倒立，为负说明图像是正的
    u_int16_t biPlanes;   //为目标设备说明颜色平面数，总被设置为1
    u_int16_t biBitCount;   //说明像素比特数 1，2，4，8，16，24，32
    u_int32_t biCompression;   // 压缩格式，0表示不压缩
    u_int32_t biSizeImage;   // 位图数据的大小，当用BI_RGB格式时，可以设置为0；
    u_int32_t biXPelsPerMeter;   //水平分辨率，单位是像素/米
    u_int32_t biYPelsPerMeter;   //垂直分辨率，单位是像素/米
    u_int32_t biClrUsed;   //说明位图使用的调色板中的颜色索引数，为0说明使用所有
    u_int32_t biClrImportant;   //说明对图像显示有重要影响的颜色索引数，为0说明都重要
}BITMAPINFODEADER, *BITMAPFILEHEADER_P ;  
#pragma pack();






#pragma pack(1);
typedef struct bmp_picinfo
{
	const char *pathname; // 文件路径
	char *pic_data;
	int fd;
	u_int16_t bfType;   // 文件类型
    u_int32_t bfSize;   // 文件大小 
    u_int32_t bfOffBits;   // 从文件头到位图数据的偏移量
    u_int32_t biWidth;   // 位图的像素宽
    u_int32_t biHeight;   //位图的像素高，如果为正说明图像倒立，为负说明图像是正的
    u_int16_t biBitCount;   //说明像素比特数 1，2，4，8，16，24，32
    u_int32_t biCompression;   // 压缩格式，0表示不压缩
    u_int32_t biSizeImage;   // 位图数据的大小，当用BI_RGB格式时，可以设置为0；
}bmp_picinfo;
#pragma pack();


#pragma pack(1);// jpeg 结构体
typedef struct jpeg_picinfo
{
	const char *pathname; // 文件路径
	char *pic_data;
	FILE *infile;
	int fd;
	u_int16_t bfType;   // 文件类型
    u_int32_t bfSize;   // 文件大小 
    u_int32_t bfOffBits;   // 从文件头到位图数据的偏移量
    u_int32_t biWidth;   // 位图的像素宽
    u_int32_t biHeight;   //位图的像素高，如果为正说明图像倒立，为负说明图像是正的
    u_int16_t biBitCount;   //说明像素比特数 1，2，4，8，16，24，32
    u_int32_t biCompression;   // 压缩格式，0表示不压缩
    u_int32_t biSizeImage;   // 位图数据的大小，当用BI_RGB格式时，可以设置为0；
    u_int32_t length;
	unsigned char *data;    //图片数据指针
}jpeg_picinfo,*jpeg_picinfop;
#pragma pack();

//png结构体
#pragma pack(1);
typedef struct png_picin
{
	const char *pathname; // 文件路径
	unsigned char **data;
	int fd;	
	FILE *file;
	u_int16_t bfType;   // 文件类型
    u_int32_t bfSize;   // 文件大小 
    u_int32_t bfOffBits;   // 从文件头到位图数据的偏移量
    u_int32_t biWidth;   // 位图的像素宽
    u_int32_t biHeight;   //位图的像素高，如果为正说明图像倒立，为负说明图像是正的
    u_int16_t biBitCount;   //说明像素比特数 1，2，4，8，16，24，32
    u_int32_t biCompression;   // 压缩格式，0表示不压缩
    u_int32_t biSizeImage;   // 位图数据的大小，当用BI_RGB格式时，可以设置为0；
}png_picinfo, *png_picinfop;
#pragma pack();

// image_manage.h 结构体



/***********************************函数原型******************************************/
int is_bmp(const char *pathname);
int is_jpg(const char *pathname);
int is_png(const char * pathname);

void display_bmp(const      char * pdata);
int display_jpg(const char *pdata);
int display_png(const char * pathname);

void print_images(void);
//void show_image(void);
void show_image(image_info_t* image);
image_manager_t * image_manage_init();
int scan_image3(const char *path);
void TS_UPDOWN3();


#endif

