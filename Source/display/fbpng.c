




#include <stdio.h>








int is_png(const char * pathname){
	printf("i am here.\n");
	FILE *file = NULL;

	file = fopen(pathname, "rb");
	if(file == NULL){
		printf("%s fopen failed.\n", pathname);
		return -1;

	}

	printf("%s fopen success.\n", pathname);

	return 0;
}



int display_png(const char * pathname){



	return 0;
}




