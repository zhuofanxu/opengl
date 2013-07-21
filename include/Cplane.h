#ifndef _CPLANE_H_
#define _CPLANE_H_
#include"Vector.h"
struct tPlane{
	Vector3 m_vertex[3];
	Vector3 m_normal;
	Vector2 m_uv[3];
	int     m_pnumbers;
};
class Cplane
{
//protected:
	
	
public:
	Cplane();
	~Cplane();
	bool Init(int pnumbers);
	//Vector3 getVertex(int i){return m_vertex[i];}
	//Vector3 getNormal(){return m_normal;}               
	//Vector2 getuv(int i){return m_uv[i];}
    void Bedraw();
	int    m_pnum;
	tPlane *m_plist;
	Vector3 *Vertexs;
	int    vnum;
//private:
	
};
#endif


