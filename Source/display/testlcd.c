#include "config.h" 
#include <stdio.h>
#include "image_manage.h"



extern unsigned int sleep(unsigned int seconds);

extern image_info_t images[MAX_IMAGES_CNT];
extern unsigned int image_index;			// ����images�еļ���index	



void test()
{

	
	
	image_manage_init();

	scan_image3("./image_manage");

	TS_UPDOWN3();

	
	sleep(1);

	
	while(1){


	}
	
}

