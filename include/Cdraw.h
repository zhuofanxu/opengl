#ifndef _CDRAW_H_
#define _CDRAW_H_
#include"stadafx.h"
#include"Cplane.h"
#include"CbmpLoader.h"
class Cdraw
{
public:
	int DrawQuads();
	int DrawTriangle();
	void DrawBox();
	int Getpnumbers();
	//float m_angle;
	bool LoadTexture();
	void SetLight();
	void Delete();
	void  ProduceRand();
private:
	CbmpLoader m_Bmp1;
	CbmpLoader m_Bmp2;
	Cplane plane;
	int    m_rand;
};
#endif
