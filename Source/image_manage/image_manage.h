#ifndef __IMAGE_MANAGE_H_
#define __IMAGE_MANAGE_H_



#define PATHNAME_LEN 256
#define MAX_IMAGES_CNT 100
typedef enum image_type
{
	image_type_BMP,
	image_type_JPG,
	image_type_PNG,
	image_type_UNKNOW,

}image_type_e;

// 结构体用来封装一个图片的信息


typedef struct image_info{
	char pathname[PATHNAME_LEN];//图片文件的pathname
	image_type_e type;


}image_info_t, *image_info_tp;



#endif
































