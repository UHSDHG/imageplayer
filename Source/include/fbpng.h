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
	const char *pathname; // �ļ�·��
	unsigned char *data;
	int fd;	
	FILE *file;
	u_int16_t bfType;   // �ļ�����
    u_int32_t bfSize;   // �ļ���С 
    u_int32_t bfOffBits;   // ���ļ�ͷ��λͼ���ݵ�ƫ����
    u_int32_t biWidth;   // λͼ�����ؿ�
    u_int32_t biHeight;   //λͼ�����ظߣ����Ϊ��˵��ͼ������Ϊ��˵��ͼ��������
    u_int16_t biBitCount;   //˵�����ر����� 1��2��4��8��16��24��32
    u_int32_t biCompression;   // ѹ����ʽ��0��ʾ��ѹ��
    u_int32_t biSizeImage;   // λͼ���ݵĴ�С������BI_RGB��ʽʱ����������Ϊ0��
}png_picinfo, *png_picinfop;
#pragma pack();




int is_png(const char * pathname);
int display_png(const char * pathname);
#define PNG_BYTES_TO_CHECK 4




#endif






