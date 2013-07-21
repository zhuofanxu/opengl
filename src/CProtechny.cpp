#include"CProtechny.h"

bool CProtechny::Init(int num)
{
	if(CParticule::Init(num))
	{
	   for(int i=0;i<m_pnum;i++)
	   {
		float x,y,z,vx,vy,vz;
		x=0.005f*(rand()%9);
		y=0.005f*(rand()%9)-1;
	    z=0.005f*(rand()%6);
		m_parlist[i].m_pos=Vector3(x,y,z);
		vx = 0.0000007f * (rand()%9000-rand()%9000);
		vy = 0.0000042f * (rand()%9000);
		vz = 0.0000001f * (rand()%9000);
	    m_parlist[i].m_velocity = Vector3(vx,vy,vz);

			// 初始化加速度 
			m_parlist[i].m_acceleration = Vector3(0.0,-0.00025f,0.0);

			//初始化粒子生命时间 
			m_parlist[i].m_lifetime = 100;
			
			// 初始化粒子的尺寸 
			m_parlist[i].m_size = 0.01f;

			// 初始化粒子的消失速度 
			m_parlist[i].m_dec = 0.05 * (rand()%50);

			//初始化粒子的颜色 
			m_parlist[i].m_color[0] = 255.0f;
			m_parlist[i].m_color[1] = 255.0f;
			m_parlist[i].m_color[2] = 255.0f;

		}
	   if(!m_Bmp.Load("flare.bmp"))
	   {
		   MessageBox(NULL,"粒子纹理载入失败","错误",MB_OK);
	       return false;
	   }
	   else
		   return true;
  }
	else 
		return false;
}
void CProtechny::Render()
{   
	glPushMatrix();
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);      //设置混合因子获得半透明效果 
    glEnable(GL_BLEND);				     //< 启用混和 
	glEnable(GL_TEXTURE_2D);   
	glTranslatef(0.0f,-4.0f,-6.0f);
	glBindTexture(GL_TEXTURE_2D,m_Bmp.ID);     //选择纹理
	for(int i=0;i<m_pnum;i++)
	{
		float x=m_parlist[i].m_pos.x;
	    float y=m_parlist[i].m_pos.y;
		float z=m_parlist[i].m_pos.z;
		float size=m_parlist[i].m_size;
		glColor3fv(m_parlist[i].m_color);
		glNormal3f(0.0f,0.0f,1.0f);
		glBegin(GL_QUADS);                   //绘制粒子
		    glTexCoord2f(0.0f,0.0f);glVertex3f(x-size,y-size,z);
			glTexCoord2f(1.0f,0.0f);glVertex3f(x+size,y-size,z);
			glTexCoord2f(1.0f,1.0f);glVertex3f(x+size,y+size,z);
			glTexCoord2f(0.0f,1.0f);glVertex3f(x-size,y+size,z);
		glEnd(); 
	

    }    
	    glDisable(GL_BLEND);
		glPopMatrix();
	Upadate();
}
void CProtechny::Upadate()
{
	for(int i=0;i<m_pnum;i++)
	{          //更新位置                        
		m_parlist[i].m_pos.x+=m_parlist[i].m_velocity.x;
		m_parlist[i].m_pos.y+=m_parlist[i].m_velocity.y;
		m_parlist[i].m_pos.z+=m_parlist[i].m_velocity.z;
		       //更新速度
		m_parlist[i].m_velocity.y+=m_parlist[i].m_acceleration.y;
		      //更新生时间
		m_parlist[i].m_lifetime-=m_parlist[i].m_dec;

		if(m_parlist[i].m_pos.y<=-1||m_parlist[i].m_lifetime<=0)
		{
		float x,y,z,vx,vy,vz;	
		x=0.005f*(rand()%9);
		y=0.005f*(rand()%9)-1;
	    z=0.005f*(rand()%6);
		m_parlist[i].m_pos=Vector3(x,y,z);
		vx = 0.0000007f * (rand()%9000-rand()%9000);
		vy = 0.0000042f * (rand()%9000);
		vz = 0.0000001f * (rand()%9000);
	    m_parlist[i].m_velocity = Vector3(vx,vy,vz);

			// 初始化加速度 
		m_parlist[i].m_acceleration = Vector3(0.0,-0.00025f,0.0);

			//初始化粒子生命时间 
		m_parlist[i].m_lifetime = 100;
			
			// 初始化粒子的尺寸 
		m_parlist[i].m_size = 0.01f;

			// 初始化粒子的消失速度 
		m_parlist[i].m_dec = 0.05 * (rand()%50);

		}
  }
}
