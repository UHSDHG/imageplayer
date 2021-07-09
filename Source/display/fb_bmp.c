
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
*函数名：is_bmp(const unsigned char *pdata);
*函数功能：判断是否为 bmp图片
*
*参数：
*返回值：-1 表示不是bmp ， 0表示是bmp
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
*函数名：analysis_bmp(const unsigned char * pdata)
*函数功能：解析bmp图片，并使用fb_draw显示图片
*
*参数：bmp数据的头指针
*返回值：无
*/

void analysis_bmp(const unsigned char * pdata){




}






