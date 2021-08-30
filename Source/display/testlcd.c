
#include <stdio.h>
#include "fbbmp.h"
#include "fbjpeg.h"
#include "fbpng.h"
#include "config.h"



extern unsigned int sleep(unsigned int seconds);

void test()
{


	//analysis_bmp(open_bmp_Willo_lake);
	while(1){
	debug("test-------------------------\n");
	//display_png(open_png_sakura);
	//display_png(open_png_Jey);
	debug("/n is_png(open_png_GEM) = %d.\n",is_png(open_png_GEM));
	debug("/n is_png(open_bmp_sakura) = %d.\n",is_png(open_bmp_sakura));
	//display_jpeg(open_jpeg_sakura);
	sleep(1);

	debug("-------------------------test\n\n\n");


	}
	
}

