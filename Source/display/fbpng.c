/*
参考代码：https://blog.csdn.net/weixin_42462202/article/details/84937879
https://www.cnblogs.com/xiaoxiaoboke/archive/2012/02/13/2349765.html


*/




#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#include <png.h>
#include <pngstruct.h>
#include <pngconf.h>
#include <pnginfo.h>





int is_png(const char * pathname){
	debug("I am here.\n");
	FILE *fp = NULL;
	char buf[PNG_BYTES_TO_CHECK];
	
	/* Open the prospective PNG file. */
	if ((fp = fopen(pathname, "rb")) == NULL)
		return -1;
	debug("fopen %s success.\n", pathname);
	/* Read in some of the signature bytes. */
	if (fread(buf, 1, PNG_BYTES_TO_CHECK, fp) != PNG_BYTES_TO_CHECK){
	fclose(fp);
	return -1;
	}
	debug("fread %s success.\n", pathname);	
	
	/* Compare the first PNG_BYTES_TO_CHECK bytes of the signature.
	* Return nonzero (true) if they match.
	*/
	fclose(fp);
	return(png_sig_cmp(buf, 0, PNG_BYTES_TO_CHECK));

}

static int read_png(png_picinfop pic_data){
	   debug("I am here.\n");
	   

	   png_structp png_ptr;
	   png_infop info_ptr;
	   int sig_read = 0;
	   png_uint_32 width, height;
	   int bit_depth, color_type, interlace_type;
	   FILE *fp;

	   	// 打开文件
	   if ((fp = fopen(pic_data->pathname, "rb")) == NULL){
			debug("fopen %s failed.\n", pic_data->pathname);
			return -1;
	   }
	debug("fopen %s success.\n", pic_data->pathname);
	   /* Create and initialize the png_struct with the desired error handler
		* functions.  If you want to use the default stderr and longjump method,
		* you can supply NULL for the last three parameters.  We also supply the
		* the compiler header file version, so that we know if the application
		* was compiled with a compatible version of the library.  REQUIRED. 	
		使用所需的错误处理程序创建并初始化png_struct  
		*功能。 如果你想使用默认的stderr和longjump方法，  
		*您可以为最后三个参数提供NULL。 我们也提供  
		*编译器头文件版本，以便我们知道应用程序是否  
		*是用兼容的库版本编译的。 必需的。	
	
		*/

	   // 实例化png_ptr解码器指针与info_ptr png信息结构体
	   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	
	   if (png_ptr == NULL)
	   {
		  fclose(fp);
		  return -1;
	   }
	
	   /* Allocate/initialize the memory for image information.  REQUIRED. 
	   为映像信息分配/初始化内存。 必需的。  */
	   info_ptr = png_create_info_struct(png_ptr);
	   if (info_ptr == NULL)
	   {
		  fclose(fp);
		  png_destroy_read_struct(&png_ptr, NULL, NULL);
		  return -1;
	   }
	
	   /* Set error handling if you are using the setjmp/longjmp method (this is
		* the normal method of doing things with libpng).  REQUIRED unless you
		* set up your own error handlers in the png_create_read_struct() earlier.
		如果您正在使用setjmp/longjmp方法(这是  
	*使用libpng做事情的正常方法)。 除非你要求  
	*在前面的png_create_read_struct()中设置自己的错误处理程序。  
		*/
	   if (setjmp(png_jmpbuf(png_ptr)))
	   {
		  /* Free all of the memory associated with the png_ptr and info_ptr.
		  释放与png_ptr和info_ptr相关的所有内存	*/
		  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		  fclose(fp);
		  /* If we get here, we had a problem reading the file.
		  到了这里，我们在读取文件时遇到了问题。  */
		  return -1;
	   }

	   /* One of the following I/O initialization methods is REQUIRED.
	   下列I/O初始化方法之一是必需的。  */
	   
	   /* Set up the input control if you are using standard C streams.
	   如果使用标准的C流，则设置输入控件。  */
	   png_init_io(png_ptr, fp);

		png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_STRIP_ALPHA, NULL);
 
	if ((png_ptr != NULL) && (info_ptr != NULL))
	{
		/* 获取图像的宽高 */
		width = png_get_image_width(png_ptr, info_ptr);       
		height = png_get_image_height(png_ptr, info_ptr); 
		debug("width:%d,height:%d\n", width, height);
 
        /* 获取图像颜色类型 */
	    color_type = png_get_color_type(png_ptr, info_ptr); 
        debug("color type:%d\n", color_type);
		pic_data->biWidth = width;
		pic_data->biHeight = height;
 
    }
 
    /* 获取所有的图像数据 */
    png_bytep *row_pointers; /* 指针数组，数组中的每一个指针都指向一行图像数据 */
    row_pointers = png_get_rows(png_ptr, info_ptr);
 
    int i, j;
    int pos = 0;
 
	/* RGB格式 */
    if(PNG_COLOR_TYPE_RGB == color_type)
    {
        /* 图像数据的大小 */
        int image_size = width * height * 3;   
        unsigned char *p_image = malloc(image_size);// 在display_png图片中
		pic_data->data = p_image;
 
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < (width * 3); j += 3)
            {
                *(p_image + pos++) = row_pointers[i][j + 2];
                *(p_image + pos++) = row_pointers[i][j + 1];
                *(p_image + pos++) = row_pointers[i][j + 0];
               
            }
        }
 
    }   

	   /* Clean up after the read, and free any memory allocated.  REQUIRED.读取后进行清理，并释放分配的任何内存。必需的。 */
	   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	
	   /* Close the file. 关闭该文件。*/
	   fclose(fp);






	return 0;
}

int display_png(const char * pathname){
	png_picinfop pic_data = NULL;
	pic_data = (png_picinfop)malloc(sizeof( struct png_picin));// 在胡本函数display_png末尾释放
	pic_data->pathname = pathname;

	
	// 判断是否为png图片
	if(is_png(pic_data->pathname)){
		debug("%s is not png file.\n",pic_data->pathname);
		return -1;
	}
	debug("%s is png file.\n", pic_data->pathname);

	// read png
	read_png(pic_data);
	debug("read_png finish.\n");

	// display png
	fb_open();
	fb_draw_png(pic_data);

	//释放资源
	free(pic_data->data);
	free(pic_data);
	
	return 0;
}




