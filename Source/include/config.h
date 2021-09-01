#ifndef __CONFIG_H_
#define __CONFIG_H_


#include <stdio.h>

#include <sys/types.h>

//#undef DEBUG //������

/*************************************���Ժ�*****************************************/

#ifdef DEBUG
#define debug(format, ...)   fprintf(stderr,"[debug][%s:%s:%d] "format"",\
               __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else


#define debug(...)
#endif

/*************************************��������*****************************************/


 
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



/**********************************�ṹ���װ******************************************/
//bmp
//���������ṹ��λͼ�Ľṹ  
#pragma pack(1);
// �ļ�ͷ�ṹ��
typedef struct BITMAPFILEHEADER  
{   
    u_int16_t bfType;   // �ļ�����
    u_int32_t bfSize;   // �ļ���С
    u_int16_t bfReserved1;    //����
    u_int16_t bfReserved2;   
    u_int32_t bfOffBits;   // ���ļ�ͷ��λͼ���ݵ�ƫ����
}BITMAPFILEHEADER;   

#pragma pack();


#pragma pack(1);
// ��Ϣͷ�ṹ��
typedef struct BITMAPINFOHEADER  
{   
    u_int32_t biSize;   //��Ϣͷ��С
    u_int32_t biWidth;   // λͼ�����ؿ�
    u_int32_t biHeight;   //λͼ�����ظߣ����Ϊ��˵��ͼ������Ϊ��˵��ͼ��������
    u_int16_t biPlanes;   //ΪĿ���豸˵����ɫƽ�������ܱ�����Ϊ1
    u_int16_t biBitCount;   //˵�����ر����� 1��2��4��8��16��24��32
    u_int32_t biCompression;   // ѹ����ʽ��0��ʾ��ѹ��
    u_int32_t biSizeImage;   // λͼ���ݵĴ�С������BI_RGB��ʽʱ����������Ϊ0��
    u_int32_t biXPelsPerMeter;   //ˮƽ�ֱ��ʣ���λ������/��
    u_int32_t biYPelsPerMeter;   //��ֱ�ֱ��ʣ���λ������/��
    u_int32_t biClrUsed;   //˵��λͼʹ�õĵ�ɫ���е���ɫ��������Ϊ0˵��ʹ������
    u_int32_t biClrImportant;   //˵����ͼ����ʾ����ҪӰ�����ɫ��������Ϊ0˵������Ҫ
}BITMAPINFODEADER ;  
#pragma pack();

BITMAPFILEHEADER bmp_bitmaphead;




#pragma pack(1);


typedef struct bmp_picinfo
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
}bmp_picinfo;
#pragma pack();

// jpeg �ṹ��
#pragma pack(1);
typedef struct jpeg_picinfo
{
	const char *pathname; // �ļ�·��
	char *pic_data;
	FILE *infile;
	int fd;
	u_int16_t bfType;   // �ļ�����
    u_int32_t bfSize;   // �ļ���С 
    u_int32_t bfOffBits;   // ���ļ�ͷ��λͼ���ݵ�ƫ����
    u_int32_t biWidth;   // λͼ�����ؿ�
    u_int32_t biHeight;   //λͼ�����ظߣ����Ϊ��˵��ͼ������Ϊ��˵��ͼ��������
    u_int16_t biBitCount;   //˵�����ر����� 1��2��4��8��16��24��32
    u_int32_t biCompression;   // ѹ����ʽ��0��ʾ��ѹ��
    u_int32_t biSizeImage;   // λͼ���ݵĴ�С������BI_RGB��ʽʱ����������Ϊ0��
    u_int32_t length;
	unsigned char *data;    //ͼƬ����ָ��
}jpeg_picinfo,*jpeg_picinfop;
#pragma pack();

//png�ṹ��
#pragma pack(1);


typedef struct png_picin
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


/***********************************����ԭ��******************************************/







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























