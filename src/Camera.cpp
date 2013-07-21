//========================================================
/**
*  @file      Camera.cpp
*
*  项目描述： 摄像机漫游
*  文件描述:  摄像机类  
*  适用平台： Windows98/2000/NT/XP
*  
*  作者：     WWBOSS
*  电子邮件:  wwboss123@gmail.com
*  创建日期： 2006-12-06	
*  修改日期： 2006-12-07
*
*/     
//=======================================================
#include"Camera.h"

Camera* Camera::m_pCamera = NULL;

/** 构造函数 */
Camera::Camera()
{
	/** 初始化向量值 */
	Vector3 zero = Vector3(0.0, 0.0, 0.0);		
	Vector3 view = Vector3(0.0, 0.0, 0.0);		
	Vector3 up   = Vector3(0.0, 0.0, 1.0);		
    
	/** 初始化摄像机 */
	m_Position	= zero;					
	m_View		= view;				
	m_UpVector	= up;	
	m_Speed     = 0.1f;
	count=0;
	m_pCamera = this;
}


Camera::~Camera()
{
}

/** 设置摄像机的位置,朝向和向上向量 */
void Camera::setCamera( float positionX, float positionY, float positionZ,
				  		float viewX,     float viewY,     float viewZ,
						float upVectorX, float upVectorY, float upVectorZ)
{
	/** 构造向量 */
	Vector3 Position	= Vector3(positionX, positionY, positionZ);
	Vector3 View		= Vector3(viewX, viewY, viewZ);
	Vector3 UpVector	= Vector3(upVectorX, upVectorY, upVectorZ);

	/** 设置摄像机 */
	m_Position = Position;	
	m_View     = View;			
	m_UpVector = UpVector;	
}

/**  旋转摄像机方向  */
void Camera::rotateView(float angle, float x, float y, float z)
{
	Vector3 newView;

	/** 计算方向向量 */
	Vector3 view = m_View - m_Position;		

	/** 计算 sin 和cos值 */
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	/** 计算旋转向量的x值 */
	newView.x  = (cosTheta + (1 - cosTheta) * x * x)		* view.x;
	newView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* view.y;
	newView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* view.z;

	/** 计算旋转向量的y值 */
	newView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* view.x;
	newView.y += (cosTheta + (1 - cosTheta) * y * y)		* view.y;
	newView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* view.z;

	/** 计算旋转向量的z值 */
	newView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* view.x;
	newView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* view.y;
	newView.z += (cosTheta + (1 - cosTheta) * z * z)		* view.z;

	/** 更新摄像机的方向 */
	m_View = m_Position + newView;
}

/** 用鼠标旋转摄像机 */
void Camera::setViewByMouse()
{
	POINT mousePos;									  /**< 保存当前鼠标位置 */
	int middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; /**< 得到屏幕宽度的一半 */
	int middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; /**< 得到屏幕高度的一半 */
	float angleY = 0.0f;							  /**< 摄像机左右旋转角度 */
	float angleZ = 0.0f;		                      /**< 摄像机上下旋转角度 */					
	static float currentRotX = 0.0f;
	
	/** 得到当前鼠标位置 */
	GetCursorPos(&mousePos);						
	ShowCursor(false);
	
	/** 如果鼠标没有移动,则不用更新 */
	if( (mousePos.x == middleX) && (mousePos.y == middleY) )
		return;

	/** 设置鼠标位置在屏幕中心 */
	SetCursorPos(middleX, middleY);	
	
	/**< 得到鼠标移动方向 */
	angleY = (float)( (middleX - mousePos.x) ) / 1000.0f;		
	angleZ = (float)( (middleY - mousePos.y) ) / 1000.0f;		

    static float lastRotX = 0.0f;      /**< 用于保存旋转角度 */
 	lastRotX = currentRotX; 
	
	/** 跟踪摄像机上下旋转角度 */
	currentRotX += angleZ;
 
	/** 如果上下旋转弧度大于1.0,我们截取到1.0并旋转 */
	if(currentRotX > 1.0f)     
	{
		currentRotX = 1.0f;
		
		/** 根据保存的角度旋转方向 */
		if(lastRotX != 1.0f) 
		{
			/** 通过叉积找到与旋转方向垂直的向量 */
			Vector3 vAxis = m_View - m_Position;
			vAxis = vAxis.crossProduct(m_UpVector);
			vAxis = vAxis.normalize();
			
			///旋转
			rotateView( 1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	/** 如果旋转弧度小于-1.0,则也截取到-1.0并旋转 */
	else if(currentRotX < -1.0f)
	{
		currentRotX = -1.0f;
				
		if(lastRotX != -1.0f)
		{
			
			/** 通过叉积找到与旋转方向垂直的向量 */
			Vector3 vAxis = m_View - m_Position;
			vAxis = vAxis.crossProduct(m_UpVector);
			vAxis = vAxis.normalize();
			
			///旋转
			rotateView( -1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	/** 否则就旋转angleZ度 */
	else 
	{	
		/** 找到与旋转方向垂直向量 */
		Vector3 vAxis = m_View - m_Position;
		vAxis = vAxis.crossProduct(m_UpVector);
		vAxis = vAxis.normalize();
	
		///旋转
		rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	/** 总是左右旋转摄像机 */
	rotateView(angleY, 0, 1, 0);
}


/** 左右移动摄像机 */
void Camera::yawCamera(float speed)
{
	Vector3 yaw;
	Vector3 cross = m_View - m_Position;
	cross = cross.crossProduct(m_UpVector);

	///归一化向量
	yaw = cross.normalize();
 
	m_Position.x += yaw.x * speed;
	m_Position.z += yaw.z * speed;

	m_View.x += yaw.x * speed;
	m_View.z += yaw.z * speed;


}

/** 前后移动摄像机 */
void Camera::moveCamera(float speed)
{
	/** 计算方向向量 */
	Vector3 vector = m_View - m_Position;
	vector = vector.normalize();/**< 单位化 */

    m_Position.x += vector.x * speed;    /**< 根据速度更新位置 */
	m_Position.z += vector.z * speed;	
	m_Position.y += vector.y * speed;
	
	m_View.x += vector.x * speed;		 /**< 根据速度更新方向 */	
	m_View.y += vector.y * speed;
	m_View.z += vector.z * speed;
	

}

/** 设置视点 */
void Camera::setLook()
{
	
	/** 设置视口 */
	gluLookAt(m_Position.x, m_Position.y, m_Position.z,	
			  m_View.x,	 m_View.y,     m_View.z,	
			  m_UpVector.x, m_UpVector.y, m_UpVector.z);
}


void Camera::CheckCameraCollision(Vector3 *pVertices, int numOfVerts)
{
   m_radius=(m_Position-m_View).length();
   for(int i = 11; i >= 0; i -= 3)
	{
		// 读取三角行顶点数据
		Vector3 vTriangle[3] ;
		vTriangle[0]=pVertices[i];
		vTriangle[1]=pVertices[i-1];
		vTriangle[2]=pVertices[i-2];
		Vector3 vLine[2];
		vLine[0]=m_Position;
		vLine[1]=m_View;
		// 1) 找到球体的类别（在平面的前，后，相交）
		// 法线数据
		Vector3 vNormal;
        vNormal=Normal(vTriangle);
		// 存储球体到平面的距离
		float distance = 0.0f;
		float originDistance=0.0f;
		// 确定球体与平面的关系
		//if(IntersectedPlane(vTriangle, vLine, vNormal, originDistance))//线段与平面是否相交)
		//{
			//Vector3 vIntersection=IntersectionPoint(vNormal,  vLine, distance);
		int classification = ClassifySphere(m_Position, vNormal, vTriangle[0], m_radius, distance);
        // 如果相交，做进一步检查
		if(classification == INTERSECTS) 
		{
			// 2) 找到平面上的伪交点

			// 在平面上找到球体中心的投影
		    Vector3 vOffset = vNormal * distance;
			Vector3 vIntersection = m_Position-vOffset;
			///交点在多边形内或者与多变形的边相交
			if(InsidePolygon(vIntersection, vTriangle, 3) ||
			   EdgeSphereCollision(m_Position, vTriangle, 3, m_radius / 2))
			{
				
				//Vector3 vOffset= GetCollisionOffset(vNormal, m_radius, distance);
				count++;
			}
		}
	}
}
