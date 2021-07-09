
#include<stdio.h>
#include<fbbmp.h>

#include "fbbmp.h"


extern unsigned int sleep(unsigned int seconds);

void test()
{


	analysis_bmp(open_bmp_Willo_lake);
	while(1){

	analysis_bmp(open_bmp_wangderearth1);
	sleep(2);
	analysis_bmp(open_bmp_mountainlu);
	sleep(2);
	
	analysis_bmp(open_bmp_Willo_lake);
	sleep(2);

	analysis_bmp(open_bmp_sakura);
	sleep(2);

	printf("test\n-------------------------");
	analysis_bmp(open_bmp_penguin1);
	sleep(2);

	}
	
}

