#include "config.h" 
#include <stdio.h>
#include "image_manage.h"



extern unsigned int sleep(unsigned int seconds);

extern image_info_t images[MAX_IMAGES_CNT];
extern unsigned int image_index;			// ����images�еļ���index	



void test()
{

	


	scan_image2("./image_manage");

	TS_UPDOWN();

	
	sleep(1);

	
	while(1){


	}
	
}

