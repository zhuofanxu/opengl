#ifndef _COLIDE_H
#define _COLIDE_H
//#include"Camera.h"
//#include"Cplane.h"
#include <math.h>
#include"Vector.h"
//#include"Cplane.h"
//#include"Camera.h"
class Colide
{
public:
	
	bool  ColidCheck();
	double triangleArea(Vector3 v1,Vector3 v2,Vector3 v3);
	bool   Intriangle( Vector3 v0,Vector3 v1,Vector3 v2,Vector3 v3);
private:
	//tPlane *Plist;
	//Cplane   plane;
	//Camera  m_Camera;
};
#endif