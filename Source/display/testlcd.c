
#include<stdio.h>
#include<fbbmp.h>
#include"fbjpeg.h"
#include"config.h"


extern unsigned int sleep(unsigned int seconds);

void test()
{


	//analysis_bmp(open_bmp_Willo_lake);
	while(1){
	printf("test-------------------------\n");
	display_jpeg(open_jpeg_GEM);
	sleep(2);

	printf("-------------------------test\n\n\n");


	}
	
}

