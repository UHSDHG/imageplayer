#include <stdio.h>
#include <string.h>


#include <png.h>


#include "fbpng.h"
#include "config.h"


int is_png(const char * pathname){
	debug("i am here.\n");

	FILE *file = NULL;
	file = fopen(pathname, "rb");
	if(NULL == file){
		debug("file fopen failed.\n");
		return -1;
	}
	debug("file fopen success. file = %p\n", file);

	unsigned char buf[PNG_BYTES_TO_CHECK];
	memset(buf, 0, PNG_BYTES_TO_CHECK);
	if(fread(buf, 1, PNG_BYTES_TO_CHECK, file) != PNG_BYTES_TO_CHECK){
		debug("file fread failed.\n");
		debug("buf = %s\n", buf);
		fclose(file);
		return -1;
	}
	debug("file fread success.\n");

	fclose(file);
	return (png_sig_cmp(buf, 0, PNG_BYTES_TO_CHECK));

}
























