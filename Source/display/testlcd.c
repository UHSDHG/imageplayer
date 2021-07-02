
#include<stdio.h>
#include<fb.h>

extern unsigned int sleep(unsigned int seconds);

void test()
{
		
	printf("image_player\n");
	fb_open();
	

	
	while(1){
	fb_draw_picture_small(gImage_Card_Captor_Sakura, 1024, 600);
	sleep(1);


	}
	
}

