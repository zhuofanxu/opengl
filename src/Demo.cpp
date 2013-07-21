#include"Demo.h"
GLApplication *GLApplication::Create(const char* class_name)//创建程序实例
{
	Demo * demo = new Demo(class_name);
	return reinterpret_cast<GLApplication *>(demo);
}
Demo::Demo(const char *class_name):GLApplication(class_name)
{
}
bool Demo::Init()
{
   glClearColor(0.0f,0.0f,0.0f,0.5f);
   glClearDepth(1.0f);
   glDepthFunc(GL_LEQUAL);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
   m_Camera.SetCameraradius(1);
   ResizeDraw(true);
   if(!m_protechny.Init(5000))
	{
		MessageBox(NULL,"喷泉系统初始化失败!","错误",MB_OK);
		exit(-1);
	}
   m_3ds.Init("model.3ds");
   if(!m_draw.LoadTexture())
	   MessageBox(NULL,"载入纹理失败","错误",MB_OK);
   /** 设置摄像机 */
   m_Camera.setCamera(0.0f,-3.5f, 0.0f, 0.0f, -3.5f, -0.1f,0.0f, 1.0f, 0.0f);
   m_draw.SetLight();
   return true;

}
void Demo::Uninit()
{
	
	m_draw.Delete();
	 
}

void Demo::Draw()											
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();
	plane.Init(4);
	m_Camera.CheckCameraCollision(plane.Vertexs, 12);      
	m_Camera.setLook();
	
	                        // 绘制过程
	Show3DS(m_3ds.GetmPosition().x,-5.0f,m_3ds.GetmPosition().z);
	m_draw.DrawBox();
	m_draw.DrawQuads();
	m_protechny.Render();
	PrintText();
	glFlush();						//强制执行所有的OpenGL绘制命令
	Sleep((1.0/70-1.0/380)*1000);

}

/** 更新摄像机 */
void Demo::UpdateCamera()
{
	m_Camera.setViewByMouse();
	
	/** 键盘按键响应 */
	if(m_Keys.IsPressed(VK_SHIFT))                      /**< 按下SHIFT键时加速 */
	{
		m_Camera.setSpeed(0.2f);
	}
	if(!m_Keys.IsPressed(VK_SHIFT))
	{
		m_Camera.setSpeed(0.1f);
	}
	if( m_Keys.IsPressed('W'))/**< 向上方向键或'W'键按下 */
	{	
		
		m_Camera.moveCamera(m_Camera.getSpeed());         /**< 移动摄像机 */
	}
	

	if( m_Keys.IsPressed('S')||m_Keys.IsPressed(VK_DOWN)) /**< 向下方向键或'S'键按下 */
	{
		m_Camera.moveCamera(-m_Camera.getSpeed());         /**< 移动摄像机 */
	}
	if( m_Keys.IsPressed('A')) /**< 向左方向键或'A'键按下 */
	{
		m_Camera.yawCamera(-m_Camera.getSpeed());          /**< 移动摄像机 */
    }
	if( m_Keys.IsPressed('D')) /**< 向右方向键或'D'键按下 */
	{
		m_Camera.yawCamera(m_Camera.getSpeed());            /**< 移动摄像机 */
	}
}
void Demo::Update(DWORD milliseconds)
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					// 按ESC退出 
	{
		TerminateApplication();									
	}


	if (m_Keys.IsPressed(VK_F1) == true)					// 按F1在窗口和全屏间切换 
	{
		ToggleFullscreen();									
	}
	Upadate3ds();
	UpdateCamera();
}
void Demo::Show3DS(float x,float y,float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	m_3ds.Draw();
	glPopMatrix();
}
void Demo::Upadate3ds()
{
	m_3ds.Setspeed(0.1);
	if(m_Keys.IsPressed(VK_UP))
		m_3ds.MovemodleFB(-m_3ds.Getspeed());
	if(m_Keys.IsPressed(VK_DOWN))
		m_3ds.MovemodleFB(m_3ds.Getspeed());
	if(m_Keys.IsPressed(VK_LEFT))
		m_3ds.MovemodleLR(-m_3ds.Getspeed());
	if(m_Keys.IsPressed(VK_RIGHT))
		m_3ds.MovemodleLR(m_3ds.Getspeed());
}
void Demo::CaculateFrameRate()
{
	static float lasttime=0.0f;             //记录上次时间
	static float framepersecond=0.0f;        //保存显示的帧数
	float  currenttime=GetTickCount()*0.001f;//计算当前时间（并转为秒单位）

	framepersecond++;
	if(currenttime-lasttime>1.0f)
	{
		lasttime=currenttime;              //以上一个当前时间为新起点
		m_Fps=framepersecond;              //将一秒内帧数赋给m_Fps
		framepersecond=0;                  //帧数致0，开始记录下秒内的帧数
	}
}
void Demo::PrintText()
{
    char string[128];                               /**< 用于保存输出字符串 */
	glPushAttrib(GL_CURRENT_BIT);                   /**< 保存现有颜色属性信息 */
	glColor3f(0.0f,1.0f,1.0f);                      /**< 设置文字颜色 */

	/** 输出帧速 */
    CaculateFrameRate();                               // 计算帧速 
    sprintf(string,"FPS:%d",(int)m_Fps);               /**< 字符串赋值 */
    m_font.PrintText(string, -5.0f,3.0f);              /**< 输出字符串 */
	sprintf(string,"当前位置:X=%3.1f  Y=%3.1f  Z=%3.1f Speed=%3.1f ",   
		m_Camera.getView().x,m_Camera.getView().y ,m_Camera.getView().z,
			 m_Camera.getSpeed()); /**< 字符串赋值 */
	m_font.PrintText(string,-5.0f,3.5f);
	sprintf(string,"碰撞次数:n=%d",m_Camera.count);
	m_font.PrintText(string,-5.0f,2.5f);
	glPopAttrib();
		
}

