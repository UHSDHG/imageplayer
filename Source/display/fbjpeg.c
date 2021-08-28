#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#include <string.h>
#include "config.h"
#include "fbjpeg.h"

#include <jpeglib.h>
#include <setjmp.h>





/*
*function: is_jpeg()int is_jpeg(jpeg_picinfop *pic_data)
*is jpeg file of check pic 
*output: return 0 is jpeg , 1 is not jpeg
*/
int is_jpeg(jpeg_picinfop pic_data){
	int ret = 0;
	unsigned int data =0;

	
	debug("i am here\n");
	debug("pic_data->pathname = %s\n", pic_data->pathname);


	
	if ((pic_data->infile = fopen(pic_data->pathname, "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", pic_data->pathname);
		return -1;
	  }
	debug("open file success.\n");

	// 读取文件首位两个字节，判断是否匹配
	fread(&data, 2, 1, pic_data->infile);
	debug("data = %x\n", data);
	switch (data)
		{
		case 0xd8ff:ret = 0; break;
		case 0xd9ff:ret = 0; break;
		default:ret = -1;break;
		}

	fclose(pic_data->infile);
	return ret;
}

struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}

/*
*function: is_jpeg()int is_jpeg(jpeg_picinfop *pic_data)
*is jpeg file of check pic 
*output: return 0 is jpeg , 1 is not jpeg
*/

void read_jpeg (jpeg_picinfop pic_data){

  
 

  struct jpeg_decompress_struct cinfo;

  /* */
  struct my_error_mgr jerr;

  FILE * infile;		/* source file */
  unsigned char* buffer;		/* Output row buffer */
  int row_stride;		/* physical row width in output buffer */


  if ((infile = fopen(pic_data->pathname, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", pic_data->pathname);
    return 0;
  }
  debug("open file success.\n");


  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;

  if (setjmp(jerr.setjmp_buffer)) {
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return 0;
  }

  jpeg_create_decompress(&cinfo);



  jpeg_stdio_src(&cinfo, infile);


// 获取文件信息
  (void) jpeg_read_header(&cinfo, TRUE);

	// set deconmpress reference
	// 解压为RGB的
	cinfo.scale_num=1;

    cinfo.scale_denom=1;
    cinfo.out_color_space = JCS_RGB;


  (void) jpeg_start_decompress(&cinfo);

  row_stride = cinfo.output_width * cinfo.output_components;

  buffer = (unsigned char*)malloc(row_stride);

  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */



  pic_data->biWidth = cinfo.output_width;
  pic_data->biHeight = cinfo.output_height;

  debug("pic_data->biWidth = %d\n",pic_data->biWidth);
  debug("pic_data->biHeight = %d\n", pic_data->biHeight);
  pic_data->length = cinfo.output_height *cinfo.output_width * cinfo.output_components;
  


  unsigned char *image = NULL;
  unsigned char *pointer = NULL;
  image = (unsigned char *)malloc(pic_data->length);
  memset(image, 0, pic_data->length);
  pointer = image;
  pic_data->data = image;
  
  	debug("pic_data->data = %p\n", pic_data->data);
  	debug("pointer = %p\n", pointer);
  

	
		
  while (cinfo.output_scanline < cinfo.output_height) {

    jpeg_read_scanlines(&cinfo, &buffer, 1);
	int i = 0;
	for(i = 0; i < pic_data->biWidth; i++){
		pointer[3*i + 0] = buffer[3*i + 2];
		pointer[3*i + 1] = buffer[3*i + 1];
		pointer[3*i + 2] = buffer[3*i + 0];
	}
		
	pointer += row_stride;

 	
  }


  (void) jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);
  return 0;
}





int display_jpeg(const char * filename) 
{
	//实例化pic_data
	debug("i am here\n");
	jpeg_picinfop pic_data = NULL;
	pic_data = (jpeg_picinfop)malloc(sizeof(jpeg_picinfo));
  	pic_data->pathname = filename;

	//判断是否为jpeg文件
	 if(-1 == is_jpeg(pic_data)) {
	debug("%s not jpeg file\n", pic_data->pathname);
		return -1;
  	}
  	debug("%s is jpeg file\n", pic_data->pathname);

	// 读取jpeg文件到pic_data->data
	read_jpeg(pic_data);
	debug("read_jpeg\n");

	//显示图片
	fb_open();
	debug("fb_open\n");
	fb_draw_jpeg(pic_data);
	debug("fb_draw_jpeg\n");


	//释放资源
	free(pic_data->data);
	free(pic_data);


}







