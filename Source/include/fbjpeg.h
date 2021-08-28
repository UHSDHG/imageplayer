#ifndef __FBJPEG_H_
#define __FBJPEG_H_

#include <sys/types.h>

#define open_jpeg_sakura "./image_manage/sakura.jpeg"
#define open_jpeg_GEM "./image_manage/GEM.jpeg"
#define open_jpeg_Jey "./image_manage/Jey.jpeg"
#define open_jpeg_Jey1 "./image_manage/Jey1.jpeg"
#define open_jpeg_animal "./image_manage/animal.jpeg"



#pragma pack(1);
typedef struct jpeg_picinfo
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
    u_int32_t *length;
	unsigned char *data;
}jpeg_picinfo,*jpeg_picinfop;
#pragma pack();





int display_jpeg(const char *pdata);



#endif


























