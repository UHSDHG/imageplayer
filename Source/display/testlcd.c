
#include<stdio.h>
#include<fb.h>

extern unsigned int sleep(unsigned int seconds);

void test()
{
		
	printf("image_player\n");
	fb_open();
	

	
	while(1){
		
	fb_draw_picture_small(gImage_Card_Captor_Sakura, 1024, 600);
	sleep(2);
	//fb_draw_picture_b(gImage_Jey1);
	sleep(2);
	
	fb_draw_picture_small_anywhere(900, 0, gImage_WillowLake);
	sleep(2);

	fb_draw_picture_small_anywhere(850, 400, gImage_WillowLake);
	sleep(2);

	fb_draw_picture_small_anywhere(300, 300, gImage_WillowLake1);
	sleep(2);

	fb_draw_picture_small(gImage_mountainlu, 1024, 600);
	sleep(2);	
	}
	
}

