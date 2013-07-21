#ifndef _CBMPLOADER_H_
#define _CBMPLOADER_H_
#include"stadafx.h"
#define BITMAP_ID 0x4D42  //位图文件标志
class CbmpLoader
{
public:
	CbmpLoader();
	~CbmpLoader();
	bool LoadBitmap(const char* file); //载入一个bmp文件            
	void FreeImage();               //释放图像数据
	bool Load(const char* fileName);//载入位图并创建纹理
	unsigned int ID;                //生成纹理ID号
	int imageWidth;                 //图像宽度
	int imageHeight;                //图像高度
	unsigned char* image;           //指向图像数据指针
};
#endif