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
	const char *pathname; // �ļ�·��
	char *pic_data;
	int fd;
	u_int16_t bfType;   // �ļ�����
    u_int32_t bfSize;   // �ļ���С 
    u_int32_t bfOffBits;   // ���ļ�ͷ��λͼ���ݵ�ƫ����
    u_int32_t biWidth;   // λͼ�����ؿ�
    u_int32_t biHeight;   //λͼ�����ظߣ����Ϊ��˵��ͼ������Ϊ��˵��ͼ��������
    u_int16_t biBitCount;   //˵�����ر����� 1��2��4��8��16��24��32
    u_int32_t biCompression;   // ѹ����ʽ��0��ʾ��ѹ��
    u_int32_t biSizeImage;   // λͼ���ݵĴ�С������BI_RGB��ʽʱ����������Ϊ0��
    u_int32_t *length;
	unsigned char *data;
}jpeg_picinfo,*jpeg_picinfop;
#pragma pack();





int display_jpeg(const char *pdata);



#endif


























