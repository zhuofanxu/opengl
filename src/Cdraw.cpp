#include"Cdraw.h"

int Cdraw::DrawQuads()
{
	
	//count++;
	//定义材质属性
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	//设置材质属性
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,m_Bmp1.ID);
	glTranslatef(0.0f,0.0f,-10.0f);
	glBegin(GL_QUADS);
	
	plane.Bedraw();
	glEnd();
	 glPopMatrix();
	
	 return 0;
}


int Cdraw::DrawTriangle()
{
	int count=0;
	return count;
}
void Cdraw:: ProduceRand()
{
	static float lasttime=0.0f;             //记录上次时间
	float  currenttime=GetTickCount()*0.001f;//计算当前时间（并转为秒单位）

	if(currenttime-lasttime>1.0f)
	{
		lasttime=currenttime;              //以上一个当前时间为新起点
		m_rand=rand()%5;
	}
}
void Cdraw::DrawBox()
{
	
	// 设置材质属性 
	float m_angle=0.0f;
	GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glPushMatrix();
	ProduceRand();
	if(m_rand==0){
		glTranslatef(-0.5f,-3.5f,-7.0f);}
	else if(m_rand==1){
		glTranslatef(0.5f,-3.5f,-7.0f);}
	else if(m_rand==2){
		glTranslatef(0.5f,-3.5f,-5.0f);}
	else
		glTranslatef(-0.5f,-3.5f,-5.0f);
	glScalef(0.1f,0.2f,0.05f);
	glRotatef(m_angle,0.0f,1.0f,0.0f);
	// 选择纹理 
	glBindTexture(GL_TEXTURE_2D, m_Bmp2.ID);
	
	// 开始绘制四边形 
	glBegin(GL_QUADS);												
		
	    /// 前侧面
		glNormal3f( 0.0f, 0.0f, 1.0f);								//< 指定法线指向观察者 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  0.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.0f,  0.0f);	
		
		/// 后侧面
		glNormal3f( 0.0f, 0.0f,-1.0f);								//指定法线背向观察者 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -1.0f, -1.0f);	
		
		/// 顶面
		glNormal3f( 0.0f, 1.0f, 0.0f);								//指定法线向上 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  0.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.0f, -1.0f);	
		
		/// 底面
		glNormal3f( 0.0f,-1.0f, 0.0f);								// 指定法线朝下 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, -1.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		
		/// 右侧面
		glNormal3f( 1.0f, 0.0f, 0.0f);								// 指定法线朝右 
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  0.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -1.0f,  0.0f);	
		
		/// 左侧面
		glNormal3f(-1.0f, 0.0f, 0.0f);								// 指定法线朝左 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.0f,  0.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.0f, -1.0f);	
	glEnd();

	glPopMatrix();
}
bool Cdraw::LoadTexture()
{
	/** 载入位图文件 */
	if(!m_Bmp1.Load("2.bmp")||!m_Bmp2.Load("zhuan.bmp"))                        /**< 载入位图文件 */
	{
		MessageBox(NULL,"装载位图文件失败！","错误",MB_OK);  /**< 如果载入失败则弹出对话框 */
		return false;
	}
	/** 启用纹理映射 */
	glEnable(GL_TEXTURE_2D);

  	return true;
}
void Cdraw::SetLight()
{
	 // 定义光源的属性值 
	GLfloat LightAmbient[]= { 0.0f, 0.0f, 0.0f, 1.0f }; 	/**< 环境光参数 */
	GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };		/**< 漫射光参数 */
	GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< 镜面光参数 */
	GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };	/**< 光源位置 */
	GLfloat diffuseLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat specularLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat lightPositionB[]=  {0.0f,0.0f,0.0f,1.0f};
	/** 设置光源的属性值 */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		/**< 设置环境光 */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		/**< 设置漫射光 */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);	/**< 设置漫射光 */
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	/**< 设置光源位置 */

	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLightB);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLightB);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionB);
	/** 启用光源 */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1); 
	//glEnable(GL_LIGHT2);
}
void Cdraw::Delete()
{
	

		m_Bmp1.FreeImage();
	    glDeleteTextures(1,&m_Bmp1.ID);
		m_Bmp2.FreeImage();
		glDeleteTextures(1,&m_Bmp2.ID);
	
}