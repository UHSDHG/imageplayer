
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



#include "fb.h"
#include "fb_bmp.h"


#define open_bmp_wangderearth1 "./../image_manage/wangderearth1.bmp"
int bmp_fd = -1;
BITMAPFILEHEADER bmp_bitmaphead;



/*
*��������is_bmp(const unsigned char *pdata);
*�������ܣ��ж��Ƿ�Ϊ bmpͼƬ
*
*������
*����ֵ��-1 ��ʾ����bmp �� 0��ʾ��bmp
*/

int is_bmp(){
	int ret = 0;
	bmp_fd = open(open_bmp_wangderearth1, O_RDONLY);
	if(-1 == bmp_fd){
		printf("open\n");
		return -1;
	}

	if(-1 == read(bmp_fd, &bmp_bitmaphead, sizeof(BITMAPFILEHEADER))){
		printf("read\n");
		ret = -1;
		goto my_close_do;

	}


	
	return ret;


my_close_do:
	close(bmp_fd);
	return -1;
	


}






/*
*��������analysis_bmp(const unsigned char * pdata)
*�������ܣ�����bmpͼƬ����ʹ��fb_draw��ʾͼƬ
*
*������bmp���ݵ�ͷָ��
*����ֵ����
*/

void analysis_bmp(const unsigned char * pdata){




}






