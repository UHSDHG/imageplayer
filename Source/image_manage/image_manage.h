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

// �ṹ��������װһ��ͼƬ����Ϣ

#pragma pack(1);

typedef struct image_info{
	char pathname[PATHNAME_LEN];//ͼƬ�ļ���pathname
	image_type_e type;


}image_info_t, *image_info_tp;
#pragma pack();
#pragma pack(1);

typedef struct image_manager{
	image_info_t **images;
	int index;
	int max;
}image_manager_t;
#pragma pack();


#endif
































