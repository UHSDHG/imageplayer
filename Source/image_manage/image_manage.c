

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




// 定义存储图片信息的数组

image_info_t images[MAX_IMAGES_CNT];
unsigned int image_index = 0;			// 数组images中的计数index	

image_manager_t * image_manager = NULL;


image_manager_t * image_manage_init(){

	image_manager = (image_manager_t *)calloc(imaeg_manage_default_size, sizeof(image_manager_t));
	image_manager->images = (image_info_t**)calloc(100, sizeof(image_info_t*));
	image_manager->index = 0;
	image_manager->max = 100;

	return image_manager;

}





int scan_image3(const char *path){


	// 在本函数中递归检索path文件夹，将其中所有图片填充到iamges数组中去
	DIR *dir;
	struct dirent *ptr;
	char base[1000];
	struct stat sta;

	if ((dir = opendir(path)) == NULL)
	{
		perror("Open dir error...");
		exit(1);
	}

	// readdir函数每调用一次就会返回opendir打开的basepath目录下的一个文件，直到
	// basepath目录下所有文件都被读完之后，就会返回NULL
	while ((ptr = readdir(dir)) != NULL)
	{
		if(strcmp(ptr->d_name, ".")==0 || strcmp(ptr->d_name, "..")==0)    ///current dir OR parrent dir
			continue;

		// 用lstat来读取文件属性并判断文件类型
		memset(base,'\0',sizeof(base));
		// 得到完整的路径
		strcpy(base,path);
		strcat(base,"/");
		strcat(base,ptr->d_name);
		// 将pathname 中的 文件信息，填充到sta结构体中
		lstat(base, &sta);
		
		debug("                           base = %s\n", base);

		
		if (S_ISREG(sta.st_mode))// S_ISREG 是通过这个宏，判断base的pathname文件是否是REG文件
		{
			//printf("regular file.\n");
			//printf("d_name:%s/%s\n", path, ptr->d_name);
			// 如果是普通文件，就要在这里进行处理:
			// 处理思路就是 先判定是否属于已知的某种图片格式，如果是则放到images数组中
			// 如果都不属于则不理他

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
		// 判断是否是路径文件
		if (S_ISDIR(sta.st_mode))
		{
			//printf("directory.\n");
			//printf("d_name:%s/%s\n", path, ptr->d_name);
			scan_image3(base);//路径文件进行递归
		}
	}



}


// images数组本来是空的，然后程序初始化时会去一个事先约定好的目录(image目录)下去
// 递归检索所有的文件及子文件夹，并且将所有的图片格式收集并且填充记录到images数组中
// 经过检索后，image数组中就记录了所有的图片，然后显示图片逻辑部分再去这个图片库中
// 拿出相应的图片来显示即可
// path是要去检索的文件夹的pathname
int scan_image(const char *path)
{
	// 在本函数中递归检索path文件夹，将其中所有图片填充到iamges数组中去
	DIR *dir;
	struct dirent *ptr;
	char base[1000];

	if ((dir = opendir(path)) == NULL)
	{
		perror("Open dir error...");
		exit(1);
	}

	// readdir函数每调用一次就会返回opendir打开的basepath目录下的一个文件，直到
	// basepath目录下所有文件都被读完之后，就会返回NULL
	while ((ptr = readdir(dir)) != NULL)
	{
		if(strcmp(ptr->d_name, ".")==0 || strcmp(ptr->d_name, "..")==0)    ///current dir OR parrent dir
			continue;

		

		//debug("d_name = %s.\n", ptr->d_name);
		debug("d_type = %d, DT_REG = %d, DT_DIR = %d, DT_UNKNOWN = %d.\n", 
			ptr->d_type, DT_REG, DT_DIR, DT_UNKNOWN);
		switch (ptr->d_type)
		{
			case DT_REG:			// 普通文件
				printf("d_name:%s/%s\n", path, ptr->d_name);
				break;
			case DT_DIR:			// 文件夹
				memset(base,'\0',sizeof(base));
				strcpy(base,path);
				strcat(base,"/");
				strcat(base,ptr->d_name);
				scan_image(base);
				break;
			case DT_UNKNOWN:		// 不识别的文件格式
				printf("unknown file type.\n");
				break;
			default:
				break;
		}
	}
}

int scan_image2(const char *path)
{
	// 在本函数中递归检索path文件夹，将其中所有图片填充到iamges数组中去
	DIR *dir;
	struct dirent *ptr;
	char base[1000];
	struct stat sta;

	if ((dir = opendir(path)) == NULL)
	{
		perror("Open dir error...");
		exit(1);
	}

	// readdir函数每调用一次就会返回opendir打开的basepath目录下的一个文件，直到
	// basepath目录下所有文件都被读完之后，就会返回NULL
	while ((ptr = readdir(dir)) != NULL)
	{
		if(strcmp(ptr->d_name, ".")==0 || strcmp(ptr->d_name, "..")==0)    ///current dir OR parrent dir
			continue;

		// 用lstat来读取文件属性并判断文件类型
		memset(base,'\0',sizeof(base));
		// 得到完整的路径
		strcpy(base,path);
		strcat(base,"/");
		strcat(base,ptr->d_name);
		// 将pathname 中的 文件信息，填充到sta结构体中
		lstat(base, &sta);
		
		debug("                           base = %s\n", base);

		
		if (S_ISREG(sta.st_mode))// S_ISREG 是通过这个宏，判断base的pathname文件是否是REG文件
		{
			//printf("regular file.\n");
			//printf("d_name:%s/%s\n", path, ptr->d_name);
			// 如果是普通文件，就要在这里进行处理:
			// 处理思路就是 先判定是否属于已知的某种图片格式，如果是则放到images数组中
			// 如果都不属于则不理他
			if (!is_bmp(base))
			{
				strcpy(images[image_index].pathname, base);
				images[image_index].type = image_type_BMP;
				image_index++;
			}
			else if (!is_jpg(base))
			{
				strcpy(images[image_index].pathname, base);
				images[image_index].type = image_type_JPG;
				image_index++;
			}
			else if (!is_png(base))
			{
				strcpy(images[image_index].pathname, base);
				images[image_index].type = image_type_PNG;
				image_index++;
			}		
		}
		// 判断是否是路径文件
		if (S_ISDIR(sta.st_mode))
		{
			//printf("directory.\n");
			//printf("d_name:%s/%s\n", path, ptr->d_name);
			scan_image2(base);//路径文件进行递归
		}
	}
}

void print_images(void)
{
	int i;

	printf("iamge_index = %d.\n", image_index);
	for (i=0; i<image_index; i++)
	{
		printf("images[%d].pathname = %s,		type = %d.\n", i, images[i].pathname, images[i].type);
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
}




void TS_UPDOWN(){

//触摸检测
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
		if(ev.value < 256 ) index++;//屏幕左边
		else if(768 < ev.value) index--;
		if(index < 0) index = image_index - 1;// 屏幕
		if(index >= image_index) index = 0;
		debug("***************index is %d********************\n", index);
		show_image(&images[index]);
	}

	
	}


close(buttons_fd);


// 根据内容进行触摸操作


}

void TS_UPDOWN3(){

//触摸检测
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
		if(ev.value < 256 ) index++;//屏幕左边
		else if(768 < ev.value) index--;
		if(index < 0) index = image_manager->index - 1;// 屏幕
		if(index >= image_manager->index) index = 0;
		debug("***************index is %d********************\n", index);
		show_image(image_manager->images[index]);
	}

	
	}


close(buttons_fd);


// 根据内容进行触摸操作


}


