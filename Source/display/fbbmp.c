
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "fb.h"
#include "config.h"









/*
*��������is_bmp 
*�������ܣ��ж��Ƿ�Ϊ bmpͼƬ,��ȡ�ļ�ͷ��Ϣ�������pdata
*
*������bmp_picinfo *pdata ��һ����װbmp��Ϣ�Ľṹ��ָ��
*����ֵ��-1 ��ʾ����bmp �� 0��ʾ��bmp
*/

int is_bmp(const char *pathname){

		int ret = 0;
		int fd = 0;
		BITMAPFILEHEADER bmp_bitmaphead;
/*
		getwd(pwd_cur);
		printf("%s\n", pwd_cur);
*/
		// ��һ�����ļ����õ��ļ�id
		
		if(-1 == (fd = open(pathname , O_RDWR)))
		{
			debug("%s open failed.\n", pathname);
			return -1;
		}
		debug("open %s file success!\n", pathname);

		
		// �ڶ�������ȡ�ļ�ͷ��Ϣ
		if(-1 == read(fd, &bmp_bitmaphead, sizeof(BITMAPFILEHEADER))){
			
		debug("read\n");
		ret = -1;
		goto my_close_do;

	}
		debug("read %s  success of BITMAPFILEHEADER size!\n", pathname);


	// ���������ж��Ƿ�Ϊbmp�ļ�
	//0x4d42 ��Ӧ����char BM 
	if(0x4d42 != bmp_bitmaphead.bfType){
		debug("not is bmp file\n");
		ret = -1;
		goto my_close_do;
	}
	/*
	// ���pdata�ṹ��

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
*��������analysis_bmp
*�������ܣ�����bmpͼƬ����ʹ��fb_draw��ʾͼƬ
*
*������const char * pdata�������ļ�pathname
*����ֵ����
*/

void display_bmp(const      char * pdata){

	// ��һ����ʵ����pic_dataͼƬ���ݽṹ�� , pathname ��pic_data���
	bmp_picinfo *pic_data = NULL;
	BITMAPFILEHEADER *bmp_bitmaphead = NULL;
	
	
	pic_data = (bmp_picinfo *)malloc(sizeof(bmp_picinfo)); // display_bmp������ĩβ�ͷ�
	pic_data->pathname = pdata;

	bmp_bitmaphead = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));// display_bmp������ĩβ�ͷ�

	

	// �ڶ������ж��Ƿ�Ϊbmp�ļ�
	if(0 != is_bmp(pic_data->pathname)){
		debug("not bmp file\n");//����bmp
		goto my_end;
	}
	
	debug("%s is bmp file\n", pic_data->pathname);//����bmp
		

	// ���ļ�����ȡ�ļ�ͷ����ȡ��Ϣͷ
	


	// ���ļ�
	pic_data->fd = 0;
	if(0 >= (pic_data->fd = open(pic_data->pathname, O_RDWR))){
	debug("%s open failed, pic_data->fd = %d.\n", pic_data->pathname, pic_data->fd);
	goto my_end;

	}
	debug("%s open success, pic_data->fd = %d.\n", pic_data->pathname, pic_data->fd);
			
	// ��ȡ�ļ�ͷ
	if(-1 == read(pic_data->fd, bmp_bitmaphead, sizeof(BITMAPFILEHEADER))){
			
		debug("read bmp_bitmaphead failed\n");
		goto my_close_fd;

	}
	debug("read bmp_bitmaphead success\n");


	// �ļ�ͷ��ֵ
	
	pic_data->bfType = bmp_bitmaphead->bfType;
	pic_data->bfSize = bmp_bitmaphead->bfSize;
	pic_data->bfOffBits = bmp_bitmaphead->bfOffBits;
		debug("123\n");

	// ʵ������Ϣͷ�ṹ�壬����ȡ��Ϣͷ
	BITMAPINFODEADER *bmp_bitmapinfo = (BITMAPINFODEADER*) \
	malloc(sizeof(BITMAPINFODEADER)); // �ڱ�����display_bmp����ĩβ�ͷ�


	
	if(-1 == read(pic_data->fd, bmp_bitmapinfo, sizeof(BITMAPINFODEADER))){
		debug("bmp_bitmapinfo read failed\n");
		goto my_close_fd;
	}
	debug("bmp_bitmapinfo read success\n");
	
	// ���ṹ�壬���������
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

	// ����pdata��ͼƬ���ݿռ�
 	pic_data->pic_data = (char *)malloc(sizeof(char)*pic_data->biWidth * pic_data->biHeight * 3);// �ڱ�����display_bmp����ĩβ�ͷ�
	// �����ļ�ָ��λ�õ�ͼƬ���ݴ�
	lseek(pic_data->fd, pic_data->bfOffBits, SEEK_SET);
	// ��ȡͼƬ����
	if(-1 == read(pic_data->fd, pic_data->pic_data, pic_data->biWidth * pic_data->biHeight * 3)){
		debug("READ error\n");
		goto my_close_fd;

	}
	debug("READ success\n");


	// ��ͼ
	debug("------------draw picture of bmp------------\n");
	// ��fb�豸
	fb_open();
	// ���ú�����ͼ
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






