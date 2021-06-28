/*
*fb ������������֮ǰд�Ŀ��ô���
*
*
*/

#include "fb.h"

int fb_open()
{
	fb_fd = open(FBDEVICE, O_RDWR);
	if(fb_fd < 0)
	{
		perror("open");
		return -1;
	}

	printf("open %s device success!\n", FBDEVICE);
	
	// �ڶ�������ȡ�豸��Ӳ����Ϣ
	ret = ioctl(fd,FBIOGET_FSCREENINFO, &fb_fscreeninfo);
	if(ret < 0)
	{
                perror("get_fixed_fbscreeninfo.\n");
                return -1;
	}
	printf("open %s device var fbinfo success!\n", FBDEVICE);

	// ����������ַӳ��
	fb_pfb = (int *)mmap(NULL, fb_fscreeninfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(NULL == fb_pfb){
		perror("mmap");
	}
	
	printf("blueP\n");
	draw_back(WIDTH, HEIGHT, COLOR_BLUEP, fb_pfb);	
	
	return 0;

}

void fb_close()
{
	close(fb_fd);

}

void fb_draw_back(uint width, uint height, uint color, int *pfb)
{
	int i, j;
	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
		*(fb_pfb + i * width + j) = color;
}


void fb_draw_line(uint begin_x, uint begin_y, uint end_x, uint end_y, int *pfb)
{
	int i, k, b;
	k = (end_y - begin_y) / (end_x - begin_x);
	b = begin_y - (begin_x * k);
	for(i = begin_x; i < end_x; i++){
		*(fb_pfb + (k * i + b) + j) = color;
		}
}

































