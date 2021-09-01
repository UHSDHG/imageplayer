#ifndef __CONFIG_H_
#define __CONFIG_H_


#include <stdio.h>

#include <sys/types.h>

//#undef DEBUG //不编译

/*************************************调试宏*****************************************/

#ifdef DEBUG
#define debug(format, ...)   fprintf(stderr,"[debug][%s:%s:%d] "format"",\
               __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else


#define debug(...)
#endif

/*************************************常用配置*****************************************/


 
#define open_bmp_wangderearth1 "./image_manage/wangderearth1.bmp"
#define open_bmp_sakura "./image_manage/sakura.bmp"
#define open_bmp_mountainlu "./image_manage/mountainlu.bmp"
#define open_bmp_Willo_lake "./image_manage/Willo_lake.bmp"
#define open_bmp_penguin "./image_manage/penguin.bmp"
#define open_bmp_penguin1 "./image_manage/penguin1.bmp"


#define open_jpeg_sakura "./image_manage/sakura.jpeg"
#define open_jpeg_GEM "./image_manage/GEM.jpeg"
#define open_jpeg_Jey "./image_manage/Jey.jpeg"
#define open_jpeg_Jey1 "./image_manage/Jey1.jpeg"
#define open_jpeg_animal "./image_manage/animal.jpeg"


#define open_png_sakura "./image_manage/sakura.PNG"
#define open_png_GEM "./image_manage/GEM.PNG"
#define open_png_space "./image_manage/space.PNG"
#define open_png_Jey "./image_manage/Jey.PNG"


#define PNG_BYTES_TO_CHECK 4 



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
// 信息头结构体
typedef struct BITMAPINFOHEADER  
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
}BITMAPINFODEADER ;  
#pragma pack();

BITMAPFILEHEADER bmp_bitmaphead;




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

// jpeg 结构体
#pragma pack(1);
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
	unsigned char *data;
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


/***********************************函数原型******************************************/







int is_bmp(bmp_picinfo * pdata);
int is_jpg(const char *pathname);
int is_png(const char * pathname);



void display_bmp(const      char * pdata);

int display_jpg(const char *pdata);
int display_png(const char * pathname);




int scan_image(const char *path);
void print_images(void);
void show_images(void);










#endif
























