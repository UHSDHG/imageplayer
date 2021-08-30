#ifndef __FBPNG_H_
#define __FBPNG_H_



#include <stdio.h>
#include <sys/types.h>



#define open_png_sakura "./image_manage/sakura.png"
#define open_png_GEM "./image_manage/GEM.PNG"
#define open_png_space "./image_manage/space.png"
#define open_png_Jey "./image_manage/Jey.png"

#define open_bmp_penguin1 "./image_manage/penguin1.bmp"



#pragma pack(1);


typedef struct png_picinfo
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




int is_png(const char * pathname);
int display_png(const char * pathname);
#define PNG_BYTES_TO_CHECK 4




#endif






