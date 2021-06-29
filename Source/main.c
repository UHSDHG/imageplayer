#include<stdio.h>
#include<fb.h>
#include<images.h>

extern unsigned int sleep(unsigned int seconds);

int main(void)
{
	int i = 0;
		

	printf("image_player\n");

	 fb_open();

	 
	while(1){
	fb_draw_picture1(gImage_Card_Captor_Sakura);
	sleep(1);
	
	fb_draw_picture1(gImage_GEM);
	sleep(1);

	fb_draw_picture1(gImage_Jey1);
	sleep(1);


	}
	fb_draw_picture1(gImage_Card_Captor_Sakura);
	sleep(1);

	fb_draw_picture1(gImage_GEM);
	sleep(1);

	fb_draw_picture1(gImage_Jey1);
	sleep(1);

/*
	 for(i = 0; i < 300; i+=5){
		fb_draw_line(0, 0, 500, i, COLOR_RED);
	}
*/
	return 0;
}










































