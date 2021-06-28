#include<stdio.h>
#include<fb.h>

extern unsigned int sleep(unsigned int seconds);

int main(void)
{
	int i = 0;
		

	printf("image_player\n");

	 fb_open();

	 sleep(1);

	 fb_close();
	 	for(i; i < 300; i++){
			
		fb_draw_line(0, 0, 500, i, COLOR_RED);
		}

	return 0;
}










































