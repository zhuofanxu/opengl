#ifndef _CPROTECHNY_H_
#define _CPROTECHNY_H_
#include"CParticule.h"
#include"CbmpLoader.h"
class CProtechny:public CParticule
{
public:
	CProtechny(){}
	~CProtechny(){}
	bool       Init(int num);
	void       Render();
	void       Upadate();

private:
	CbmpLoader m_Bmp;
};
#endif 