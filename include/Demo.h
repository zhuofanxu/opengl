#ifndef _DEMO_H_
#define _DEMO_H_
#include"stadafx.h"
#include"GLFrame.h"
#include"Camera.h"
#include"Cdraw.h"
#include"C3ds.h"
#include"CFont.h"
//#include"Colide.h"
#include"CProtechny.h"
class Demo:GLApplication
{
public:
	bool Init();
	void Uninit();
	void Draw();
	void Update(DWORD milliseconds);
	void Show3DS(float x,float y,float z);
	//void process();
	void UpdateCamera();
	//void DrawBox();
	//void DrawQuads();
	//void DrawWall();
	void PrintText();
	void CaculateFrameRate();               //º∆À„÷°ÀŸ
	void Upadate3ds();
private:
	friend class GLApplication;
	Demo(const char *class_name);
	Camera m_Camera;
	Cdraw   m_draw;
	C3DSLoader m_3ds;
	GLFont  m_font;
	CProtechny m_protechny;
	float   m_Fps;
	Cplane  plane;
};
#endif