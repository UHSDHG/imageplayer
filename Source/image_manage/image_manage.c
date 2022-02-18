#include <config.h>
#include <fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include "image_manage.h"




// ����洢ͼƬ��Ϣ������
image_manager_t * image_manager = NULL;


image_manager_t * image_manage_init(){

	image_manager = (image_manager_t *)calloc(image_manage_default_size, sizeof(image_manager_t));
	image_manager->images = (image_info_t**)calloc(100, sizeof(image_info_t*));
	image_manager->index = 0;
	image_manager->max = 100;

	return image_manager;

}

// images���鱾���ǿյģ�Ȼ������ʼ��ʱ��ȥһ������Լ���õ�Ŀ¼(imageĿ¼)��ȥ
// �ݹ�������е��ļ������ļ��У����ҽ����е�ͼƬ��ʽ�ռ���������¼��images������
// ����������image�����оͼ�¼�����е�ͼƬ��Ȼ����ʾͼƬ�߼�������ȥ���ͼƬ����
// �ó���Ӧ��ͼƬ����ʾ����
// path��Ҫȥ�������ļ��е�pathname

int scan_image3(const char *path){


	// �ڱ������еݹ����path�ļ��У�����������ͼƬ��䵽iamges������ȥ
	DIR *dir;
	struct dirent *ptr;
	char base[1000];
	struct stat sta;

	if ((dir = opendir(path)) == NULL)
	{
		perror("Open dir error...");
		exit(1);
	}

	// readdir����ÿ����һ�ξͻ᷵��opendir�򿪵�basepathĿ¼�µ�һ���ļ���ֱ��
	// basepathĿ¼�������ļ���������֮�󣬾ͻ᷵��NULL
	while ((ptr = readdir(dir)) != NULL)
	{
		if(strcmp(ptr->d_name, ".")==0 || strcmp(ptr->d_name, "..")==0)    ///current dir OR parrent dir
			continue;

		// ��lstat����ȡ�ļ����Բ��ж��ļ�����
		memset(base,'\0',sizeof(base));
		// �õ�������·��
		strcpy(base,path);
		strcat(base,"/");
		strcat(base,ptr->d_name);
		// ��pathname �е� �ļ���Ϣ����䵽sta�ṹ����
		lstat(base, &sta);
		
		debug("                           base = %s\n", base);

		
		if (S_ISREG(sta.st_mode))// S_ISREG ��ͨ������꣬�ж�base��pathname�ļ��Ƿ���REG�ļ�
		{
			//printf("regular file.\n");
			//printf("d_name:%s/%s\n", path, ptr->d_name);
			// �������ͨ�ļ�����Ҫ��������д���:
			// ����˼·���� ���ж��Ƿ�������֪��ĳ��ͼƬ��ʽ���������ŵ�images������
			// �����������������

			image_info_t *image = NULL;
			if(NULL == (image = (image_info_t*)calloc(1, sizeof(image_info_t)))){
				debug("calloc failed.\n");
				exit(1);
			}
	

			if (!is_bmp(base))
			{
				strcpy(image->pathname, base);
				image->type = image_type_BMP;

			}
			else if (!is_jpg(base))
			{
				strcpy(image->pathname, base);
				image->type = image_type_JPG;

				
			}
			else if (!is_png(base))
			{
				strcpy(image->pathname, base);
				image->type = image_type_PNG;

			}
			else{
				free(image);
				image = NULL;
			}

			if(NULL != image){
				debug("********************************index = %d\n", image_manager->index);
				if(image_manager->index < image_manager->max){
					image_manager->images[image_manager->index++] = image;
					image = NULL;
					} 
				else {
					debug("too many images \n");
					exit(1);
				}
			}
		}
		// �ж��Ƿ���·���ļ�
		if (S_ISDIR(sta.st_mode))
		{
			//printf("directory.\n");
			//printf("d_name:%s/%s\n", path, ptr->d_name);
			scan_image3(base);//·���ļ����еݹ�
		}
	}



}


void print_images(void)
{
	int i;

	printf("iamge_index max = %d.\n", image_manager->index);
	for (i=0; i<image_manager->index; i++)
	{
		printf("images[%d].pathname = %s,		type = %d.\n", i, image_manager->images[i]->pathname , image_manager->images[i]->type);
	}
}
/*

void show_image(void)
{
	int i;

	for (i=0; i<image_index; i++)
	{
		switch (images[i].type)
		{
			case image_type_BMP:
				display_bmp(images[i].pathname);		break;
			case image_type_JPG:
				display_jpg(images[i].pathname);		break;
			case image_type_PNG:
				display_png(images[i].pathname);		break;
			default:
				break;
		}
		sleep(2);
	}
}
*/

void show_image(image_info_t* image)
{

	switch(image->type){
		case image_type_BMP:display_bmp(image->pathname);break;
		case image_type_JPG:display_jpg(image->pathname);break;
		case image_type_PNG:display_png(image->pathname);break;
		default:debug("image type unkonw\n");break;
	}
	sleep(1);
}


void TS_UPDOWN3(){

//�������
int buttons_fd;
int key_value, i = 0, count;
int index = 0;
struct input_event ev;
buttons_fd = open(DEVICE_KEY, O_RDWR);
if(buttons_fd < 0){
	perror("open device buttons");
	
	exit(1);
	}
	
for(;;)
{
	memset(&ev, 0, sizeof(struct input_event));
	if(0 == (count = read(buttons_fd, &ev, sizeof(struct input_event)))){
		perror("read event2fd failed!\n");
		close(buttons_fd);
		exit(1);

	}
	
	if(EV_ABS == ev.type && ABS_X == ev.code){
		if(ev.value < 256 ) index++;//��Ļ���
		else if(768 < ev.value) index--;
		if(index < 0) index = image_manager->index - 1;// ��Ļ
		if(index >= image_manager->index) index = 0;
		debug("***************index is %d********************\n", index);
		show_image(image_manager->images[index]);
	}

	
	}


close(buttons_fd);


// �������ݽ��д�������


}


