#include "config.h" 
#include <stdio.h>
#include "image_manage.h"



extern unsigned int sleep(unsigned int seconds);

extern image_info_t images[MAX_IMAGES_CNT];
extern unsigned int image_index;			// 数组images中的计数index	



void test()
{

	
	//analysis_bmp(open_bmp_sakura);
	//sleep(1);
	//display_jpeg(open_jpeg_GEM);
	
	//is_png(open_png_space);

	//analysis_bmp(open_bmp_Willo_lake);
	
	//debug("test-------------------------\n");
	//display_png(open_png_sakura);
	//display_png(open_png_Jey);
	//debug("/n is_png(open_png_GEM) = %d.\n",is_png(open_png_GEM));
	//debug("/n is_png(open_bmp_sakura) = %d.\n",is_png(open_bmp_sakura));

	scan_image2("./image_manage");
	//display_jpeg(open_jpeg_sakura);
	//debug("-------------------------test\n\n\n");
	//display_bmp(open_bmp_mountainlu);
	//print_images();
	//display_png(open_png_GEM);
	TS_UPDOWN();
	show_images();
	
	sleep(1);
	//display_png(open_png_sakura);

	
	while(1){


	}
	
}

