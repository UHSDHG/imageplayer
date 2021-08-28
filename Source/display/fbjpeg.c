#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>




#include "config.h"
#include "fbjpeg.h"


#include <jpeglib.h>

#include <setjmp.h>


jpeg_picinfop pic_data = NULL;





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



#ifdef no_compile

int display_jpeg(const char *pdata){

	//创建cinfo结构体
	// 
	struct jpeg_decompress_struct cinfo;


	struct my_error_mgr jerr;
	/* More stuff */
	FILE * infile;		  /* source file */
	JSAMPARRAY buffer;		  /* Output row buffer */
	int row_stride; /* physical row width in output buffer */



	// 打开文件
	if ((infile = fopen(pdata, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", pdata);
    return 0;
  }

	

	 /* Step 1: allocate and initialize JPEG decompression object */
	cinfo.err = jpeg_std_error(&jerr.pub);
  	jerr.pub.error_exit = my_error_exit;

	/* Establish the setjmp return context for my_error_exit to use. */
	 if (setjmp(jerr.setjmp_buffer)) {
	   /* If we get here, the JPEG code has signaled an error.
		* We need to clean up the JPEG object, close the input file, and return.
		*/
	   jpeg_destroy_decompress(&cinfo);
	   fclose(infile);
	   return 0;
	 }

	
	/* Now we can initialize the JPEG decompression object. */
	 jpeg_create_decompress(&cinfo);

	   /* Step 2: specify data source (eg, a file) */

  	jpeg_stdio_src(&cinfo, infile);


	 /* Step 3: read file parameters with jpeg_read_header() */
	(void) jpeg_read_header(&cinfo, TRUE);
	/* We can ignore the return value from jpeg_read_header since
	 *	 (a) suspension is not possible with the stdio data source, and
	 *	 (b) we passed TRUE to reject a tables-only JPEG file as an error.
	 * See libjpeg.txt for more info.
	 */

	
	 /* Step 4: set parameters for decompression */
	
	  /* In this example, we don't need to change any of the defaults set by
	   * jpeg_read_header(), so we do nothing here.
	   */
	
	  /* Step 5: Start decompressor */
	
	  (void) jpeg_start_decompress(&cinfo);
	  /* We can ignore the return value since suspension is not possible
	   * with the stdio data source.
	   */
	
	  /* We may need to do some setup of our own at this point before reading
	   * the data.	After jpeg_start_decompress() we have the correct scaled
	   * output image dimensions available, as well as the output colormap
	   * if we asked for color quantization.
	   * In this example, we need to make an output work buffer of the right size.
	   */ 
	  /* JSAMPLEs per row in output buffer */
	  row_stride = cinfo.output_width * cinfo.output_components;
	  /* Make a one-row-high sample array that will go away when done with image */
	  buffer = (*cinfo.mem->alloc_sarray)
			((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
	
	  /* Step 6: while (scan lines remain to be read) */
	  /*		   jpeg_read_scanlines(...); */
	
	  /* 
	  Here we use the library's state variable cinfo.output_scanline as the
	   * loop counter, so that we don't have to keep track ourselves.
	   这里我们使用库的状态变量cinfo。 output_scanline作为  
	*循环计数器，这样我们就不用自己跟踪了。 
	   */
	   		// pic_data 实例化
		pic_data = (jpeg_picinfop)malloc(sizeof(jpeg_picinfo));
		pic_data->pathname = pdata;
	  	pic_data->biWidth = cinfo.image_width;
	  	pic_data->biWidth = cinfo.image_height;
		pic_data->biSizeImage = (unsigned long)pic_data->biWidth * pic_data->biHeight * 24 / 8;
		pic_data->data = (unsigned char*)malloc(1024*600*3);
		debug("memory requested.\n");
		unsigned sum = 0;
	  while (cinfo.output_scanline < cinfo.output_height) {
		/* jpeg_read_scanlines expects an array of pointers to scanlines.
		 * Here the array is only one element long, but you could ask for
		 * more than one scanline at a time if that's more convenient.	   
	
		 pegg_read_scanlines期望一个指向扫描线的指针数组。  
		 *这里的数组只有一个元素长，但你可以请求  
		 *如果方便的话，一次不止一行扫描
	
		 */


		//add

		//cinfo.image_width = Width; 	/* image width and height, in pixels */ 
		//cinfo.image_height = Height;
		//cinfo.input_components = 3;	/* # of color components per pixel */
		//cinfo.in_color_space = JCS_RGB; /* colorspace of input image */



		(void) jpeg_read_scanlines(&cinfo, buffer, 1);

		int i = 0;
		
		for(i = 0; i < pic_data->biWidth; i++){
			printf("\n%x\n", buffer[i]);
			pic_data->data[sum++] = buffer[i];
		}
		debug("pic_data->data[%d] = %d\n",sum,pic_data->data[sum - 2]);
		/*
		printf("cinfo.width=%d cinfo.height=%d\n", cinfo.image_width, cinfo.image_height);
	    printf("cinfo.input_components = %d cinfo.in_color_space = %d\n", cinfo.input_components, cinfo.in_color_space);
		int i,j;
		int real_width, real_height;
		if(cinfo.image_width <= 1024) real_width = cinfo.image_width;
		else real_width = 1024;
		
		if(cinfo.image_height <= 600) real_height = cinfo.image_height;
		else real_width = 600;*/
		

		//ui32 *buffer = (ui32*)malloc(cinfo.image_width*cinfo.image_height*cinfo.)
	  	//for(i = 0; i < my_width; i++)
			
		
		/* Assume put_scanline_someplace wants a pointer and sample count. 
		假设put_scanline_某地需要一个指针和样本计数。  */

		//put_scanline_someplace(buffer[0], row_stride, );
	  }
	
	  /* Step 7: Finish decompression */
	
	  (void) jpeg_finish_decompress(&cinfo);

	  // 显示普片
	  fb_open();
	  
	  fb_draw_jpeg(pic_data);
	  // 销毁图片

	
	  
	  /* We can ignore the return value since suspension is not possible
	   * with the stdio data source.
	   我们可以忽略返回值，因为暂停是不可能的  
	*与stdio数据源。  
	   */
	
	  /* Step 8: Release JPEG decompression object 我们可以忽略返回值，因为暂停是不可能的  */
	  /* This is an important step since it will release a good deal of memory.  这是一个重要的步骤，因为它将释放大量的记忆。  */
	
	
	  
	  jpeg_destroy_decompress(&cinfo);
	
	  /* After finish_decompress, we can close the input file.
	   * Here we postpone it until after no more JPEG errors are possible,
	   * so as to simplify the setjmp error logic above.  (Actually, I don't
	   * think that jpeg_destroy can do an error exit, but why assume anything...)
	   */
	   /*	
	   在finish_decompress之后，我们可以关闭输入文件。  
	   *这里我们推迟到没有更多的JPEG错误是可能的，  
	   *来简化上面的setjmp错误逻辑。 (实际上,我不喜欢  
	   *认为jpeg_destroy可以错误退出，但为什么要假设…)  
	
	   */
	  fclose(infile);


	  
	return 0;
}



#endif






























int display_jpeg(const char * filename) 
{

  struct jpeg_decompress_struct cinfo;

  /* */
  struct my_error_mgr jerr;

  FILE * infile;		/* source file */
  unsigned char* buffer;		/* Output row buffer */
  int row_stride;		/* physical row width in output buffer */


  if ((infile = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
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
	//cinfo.scale_num=1;

    //cinfo.scale_denom=2;
    //cinfo.out_color_space = JCS_RGB;


  (void) jpeg_start_decompress(&cinfo);

  row_stride = cinfo.output_width * cinfo.output_components;

  buffer = (unsigned char*)malloc(row_stride);

  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */

  pic_data = (jpeg_picinfop)malloc(sizeof(jpeg_picinfo));
  pic_data->pathname = filename;
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
  
  int line = 0;
  	debug("pic_data->data = %p\n", pic_data->data);
  	debug("pointer = %p\n", pointer);
  

	int i = 0;
	int cnt = 0;
		
  while (cinfo.output_scanline < cinfo.output_height) {

    jpeg_read_scanlines(&cinfo, &buffer, 1);
	//debug("cnt = %d\n", cnt);

	for(i = 0; i < pic_data->biWidth; i++){
		pointer[3*i + 0] = buffer[3*i + 2];
		pointer[3*i + 1] = buffer[3*i + 1];
		pointer[3*i + 2] = buffer[3*i + 0];
	}
		
	//memcpy(pointer, buffer, row_stride);
   //debug("output_scanline = %d\n", cinfo.output_scanline);
	pointer += row_stride;
  /*buffer to image*/
 	
  }

	debug("fb_draw_jpeg\n");
	debug("pic_data->data = %p\n",pic_data->data);
	// 初始化fb
	fb_open();
 	fb_draw_jpeg(pic_data);


  (void) jpeg_finish_decompress(&cinfo);
  free(pic_data->data);
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);

  return 0;
}


















