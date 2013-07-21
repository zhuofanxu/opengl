#include"CbmpLoader.h"
#include<GL/glext.h>
CbmpLoader::CbmpLoader()
{
	image=0;
	imageWidth=0;
	imageHeight=0;
}
CbmpLoader::~CbmpLoader()
{
	FreeImage();
}
bool CbmpLoader::LoadBitmap(const char* file)
{
	FILE *pFile=0;                          //定义文件指针
	BITMAPINFOHEADER bitmapInfoHeader;      //创建位图文件位图信息和文件头结构
	BITMAPFILEHEADER header;
	unsigned char textureColors = 0;      //用于将图像颜色从BGR变换到RGB 
	pFile=fopen(file,"rb+");               //打开文件并检查错误
	if(pFile==0)                          
		return false;
	fread(&header,sizeof(BITMAPFILEHEADER),1,pFile);//读入位图文件头信息
	if(header.bfType!=BITMAP_ID)                   //检查是否为位图文件
	{
		fclose(pFile);
		return false;
	}
	fread(&bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,pFile);//读入位图文件信息
	imageWidth=bitmapInfoHeader.biWidth;                    //保存图像宽和高度
	imageHeight=bitmapInfoHeader.biHeight;
	if(bitmapInfoHeader.biSizeImage == 0)                   //确保读取数据的大小
      bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth *
      bitmapInfoHeader.biHeight * 3;
	fseek(pFile, header.bfOffBits, SEEK_SET);           //指针指向数据开始位置
	image=new unsigned char[bitmapInfoHeader.biSizeImage];//分配内存
	if(!image)                                          //检查是否分配成功
	{
		delete[] image;
		fclose(pFile);
		return false;
	}
	fread(image,bitmapInfoHeader.biSizeImage,1,pFile);   //读取图像信息
	/** 将图像颜色数据格式进行交换,由BGR转换为RGB */
	for(int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index+=3)
	   {
		   textureColors = image[index];
		   image[index] = image[index + 2];
		   image[index + 2] = textureColors;
	   }
	fclose(pFile);
	return true;
}
void CbmpLoader::FreeImage()
{
	if(image)
	{
		delete[]image;
		image=0;
	}
}
bool CbmpLoader::Load(const char* fileName)
{
	if(!LoadBitmap(fileName))
	{
		MessageBox(NULL,"载入位图文件失败!","错误",MB_OK);
		exit(0);
	}
	/** 生成纹理对象名称 */
	glGenTextures(1, &ID);
   
    /** 创建纹理对象 */
    glBindTexture(GL_TEXTURE_2D, ID);
	
	/** 控制滤波 */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
   
	/** 创建纹理 */
   	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imageWidth,
	                  imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
	                  image);
   return true;
}
