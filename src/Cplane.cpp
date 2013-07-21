#include"Cplane.h"
Cplane::Cplane()
{
	m_plist=NULL;
	m_pnum=0;
	Vertexs=NULL;
}
Cplane::~Cplane()
{
	if(m_plist!=NULL)
	{
		delete []m_plist;
		m_plist=NULL;
	}
	if(Vertexs!=NULL)
	{
	delete []Vertexs;
	Vertexs=NULL;
	}
}
bool Cplane::Init(int pnumbers)                       //平面初始化
{
	
	m_pnum=pnumbers;
	vnum=pnumbers*6;
	m_plist=new tPlane[m_pnum];
	Vertexs=new Vector3[vnum];
	Vector3 normal(0.0f,-1.0f,0.0f);
	Vector2 v0(0.0f,0.0f);
	Vector2 v1(1.0f,0.0f);
	Vector2 v2(1.0f,1.0f);
	Vector2 v3(0.0f,1.0f);
	Vector2 uv[3]={v0,v1,v3};
	Vector2 uv1[3]={v1,v2,v3};
	Vector3 vertex0(-20.0f,-5.0f,20.0f);
	Vector3 vertex1(20.0f,-5.0f,20.0f);
	Vector3 vertex2(20.0f,-5.0f,-20.0f);
	Vector3 vertex3(-20.0f,-5.0f,-20.0f);
	Vertexs[0]=vertex0;
	Vertexs[1]=vertex1;
	Vertexs[2]=vertex3;
	Vertexs[3]=vertex1;
	Vertexs[4]=vertex2;
	Vertexs[5]=vertex3;
	Vector3 vertex[3]={vertex0,vertex1,vertex3};
	Vector3 vertexq[3]={vertex1,vertex2,vertex3};
	m_plist[0].m_normal=normal;
	for(int i=0;i<3;i++)
	{
	  m_plist[0].m_uv[i]=uv[i];
	  m_plist[0].m_vertex[i]=vertex[i];
	}
	for(int i=0;i<3;i++)
	{
	  m_plist[1].m_uv[i]=uv1[i];
	  m_plist[1].m_vertex[i]=vertexq[i];
	}
	Vector3 normal1(0.0f,0.0f,1.0f);
	Vector2 v10(0.0f,0.0f);
	Vector2 v11(1.0f,0.0f);
	Vector2 v12(1.0f,1.0f);
	Vector2 v13(0.0f,1.0f);
	//Vector2 v_[3]={v10,v11,v12,v13};
	Vector3 vertex4(-20.0f,-5.0f,20.0f);
	Vector3 vertex5(-10.0f,-5.0f,20.0f);
	Vector3 vertex6(-10.0f,10.0f,20.0f);
	Vector3 vertex7(-20.0f,10.0f,20.0f);
	Vector3 vertex8(20.0f,-5.0f,20.0f);
	Vector3 vertex9(20.0f,-5.0f,-20.0f);
	Vector3 vertex10(20.0f,10.0f,-20.0f);
	Vector3 vertex11(20.0f,10.0f,20.0f);
	Vertexs[6]=vertex4;
	Vertexs[7]=vertex5;
	Vertexs[8]=vertex7;
	Vertexs[9]=vertex5;
	Vertexs[10]=vertex6;
	Vertexs[11]=vertex7;
	Vertexs[12]=vertex8;
	Vertexs[13]=vertex9;
	Vertexs[14]=vertex11;
	Vertexs[15]=vertex9;
	Vertexs[16]=vertex10;
	Vertexs[17]=vertex11;
	m_plist[1].m_normal=normal1;
	Vector3 _vertex3[3]={vertex4,vertex5,vertex7};
	Vector3 _vertex4[3]={vertex5,vertex6,vertex7};
	for(int i=0;i<3;i++)
	{
		m_plist[2].m_uv[i]=uv[i];
		m_plist[2].m_vertex[i]=_vertex3[i];
	} 
	for(int i=0;i<3;i++)
	{
		m_plist[3].m_uv[i]=uv1[i];
		m_plist[3].m_vertex[i]=_vertex4[i];
	}
	if(m_plist==NULL)
		return false;
	return true;
}
void Cplane::Bedraw()
{
	Init(4);
	
	for(int j=0;j<m_pnum;j++)
	{
		 glNormal3f(m_plist[j].m_normal.x,m_plist[j].m_normal.y,
			        m_plist[j].m_normal.z);
	 for(int i=0;i<3;i++)
	 {
		 glTexCoord2f(m_plist[j].m_uv[i].x,m_plist[j].m_uv[i].y);
		 glVertex3f(m_plist[j].m_vertex[i].x,m_plist[j].m_vertex[i].y,
		     m_plist[j].m_vertex[i].z);
	 }
	}
	
}
