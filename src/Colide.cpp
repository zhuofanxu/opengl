#include"Colide.h"


/*double Colide::triangleArea(Vector3 v1,Vector3 v2,Vector3 v3)
{
	double area;
	area=((v2-v1).crossProduct(v3-v1)).length()/2.0;
	return area;
}
bool Colide::Intriangle(Vector3 v0,Vector3 v1,Vector3 v2,Vector3 v3)
{
	double area;
	area=triangleArea(v0,v1,v2);
	area+=triangleArea(v0,v1,v3);
	area+=triangleArea(v0,v2,v3);
	double epsilon=0.01;
	if(abs(triangleArea(v1,v2,v3)-area)<epsilon)
		return true;
		return false;
}
bool Colide::ColidCheck()
{
	
	bool  flag=false;
	plane.Init(2);
    for(int i=0;i<plane.m_pnum;i++)
	{
		Vector3 P;
		Vector3 N=plane.m_plist[i].m_normal;
		float   d=plane.m_plist[i].m_normal.dotProduct(plane.m_plist[i].m_vertex[i]);
		float   t=0;
		Vector3 P0;
		Vector3 D;
		P0=m_Camera.getPosition();
		D=m_Camera.getView()-P0;
		if(D.dotProduct(N)!=0)
		{
		  t=(d-P0.dotProduct(N))/(D.dotProduct(N));
		  if(t>0&&t<=D.length())
		{
			P=P0+D*t;
			if(Intriangle(P,plane.m_plist[i].m_vertex[0],plane.m_plist[i].m_vertex[1],
				plane.m_plist[i].m_vertex[3])||Intriangle(P,plane.m_plist[i].m_vertex[1],
				plane.m_plist[i].m_vertex[2],plane.m_plist[i].m_vertex[3]))
				flag=true;
		
	    }

       }
	}
	return flag;
}*/