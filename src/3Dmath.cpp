
#include <math.h>	
#include <float.h>	
#include"3Dmath.h"
float Absolute(float num) //返回一个正数
{
	
	if(num < 0)
		return (0 - num);
	return num;
}

Vector3 Cross(Vector3 vVector1, Vector3 vVector2)//返回两个向量的叉积
{
	Vector3 vNormal;									
	vNormal=vVector1.crossProduct(vVector2);
    return vNormal;										
}

float Magnitude(Vector3 vNormal)  //返回叉积向量的数量级（长度）
{
	return (float)vNormal.length();

}

Vector3 Normalize(Vector3 vNormal) //返回单位叉级向量
{
	float magnitude = Magnitude(vNormal);			

	vNormal.x /= magnitude;							
	vNormal.y /= magnitude;								
	vNormal.z /= magnitude;						

	return vNormal;										
}

Vector3 Normal(Vector3 vPolygon[])					//返回多边形的单位法向量
{														
	Vector3 vVector1 = vPolygon[2] - vPolygon[0];   
	Vector3 vVector2 = vPolygon[1] - vPolygon[0];
	Vector3 vNormal = Cross(vVector1, vVector2);		
	vNormal = Normalize(vNormal);	
	return vNormal;
}

float Distance(Vector3 vPoint1, Vector3 vPoint2)   //返回空间两个点的距离
{
	
	double distance =(vPoint2-vPoint1).length();
	return (float)distance;
}

Vector3 ClosestPointOnLine(Vector3 vA, Vector3 vB, Vector3 vPoint)//返回线段中到一个点距离最近的点
{
	Vector3 vVector1 = vPoint - vA;
    Vector3 vVector2 = Normalize(vB - vA);
    float d = Distance(vA, vB);
	float t =vVector2.dotProduct(vVector1);
    if (t <= 0) 
		return vA;                                              //vPoint在vA侧
    if (t >= d) 
		return vB;                                               //vPoint在vB侧
    Vector3 vVector3 = vVector2 * t;
    Vector3 vClosestPoint = vA + vVector3;
	return vClosestPoint;                                 //vPoint在vA-vB间
}



float PlaneDistance(Vector3 Normal, Vector3 Point)//返回平面到原点的距离
{	
	float distance = 0;					//平面方程AX+BY+CZ=D,d=-(ax+by+cz);(a,b,c)		
    distance = - Normal.dotProduct(Point);//为单位法向量
	return distance;									
}

bool IntersectedPlane(Vector3 vPoly[], Vector3 vLine[], Vector3 &vNormal, float &originDistance)//线段与平面是否相交
{
	float distance1=0, distance2=0;				
			
	vNormal = Normal(vPoly);							
	originDistance = PlaneDistance(vNormal, vPoly[0]);
	distance1 = vNormal.dotProduct(vLine[0]);
	distance2 = vNormal.dotProduct(vLine[1]);
    if(distance1 * distance2 >= 0)			 //如果两个端点在平面同侧，不相叫，否则相交
	   return false;						
	return true;							
}


double AngleBetweenVectors(Vector3 Vector1, Vector3 Vector2)//两向量的夹角
{							
	float dotProduct =Vector1.dotProduct(Vector2);				
	float vectorsMagnitude = Magnitude(Vector1) * Magnitude(Vector2) ;
	double angle = acos( dotProduct / vectorsMagnitude );
    if(_isnan(angle))
		return 0;
	return( angle );                               //返回弧度
}

Vector3 IntersectionPoint(Vector3 vNormal, Vector3 vLine[], double distance)//计算交点
{
	distance=PlaneDistance(vNormal,  vLine[0]);
	Vector3 vPoint, vLineDir;				
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;
	vLineDir = vLine[1] - vLine[0];		
	vLineDir = Normalize(vLineDir);				
	Numerator = - (vNormal.dotProduct(vLine[0])+ distance);
	Denominator =vNormal.dotProduct(vLineDir);		
	if( Denominator == 0.0)						
		return vLine[0];						

	dist = Numerator / Denominator;			
	
	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;								
}

bool InsidePolygon(Vector3 vIntersection, Vector3 Poly[], long verticeCount)//判断交点是否在多边形内
{
	const double MATCH_FACTOR = 0.99;		// 覆盖不需要的小数位
	double Angle = 0.0;				
	Vector3 vA, vB;					
	for (int i = 0; i < verticeCount; i++)		
	{	
		vA = Poly[i] - vIntersection;		
											
		vB = Poly[(i + 1) % verticeCount] - vIntersection;
												
		Angle += AngleBetweenVectors(vA, vB);	
	}
											
	if(Angle >= (MATCH_FACTOR * (2.0 * PI)) )	// 弧度大于或等于2PI,在多边形内
		return true;							
		
	return false;								
}

bool IntersectedPolygon(Vector3 vPoly[], Vector3 vLine[], int verticeCount)
{
	Vector3 vNormal;
	float originDistance = 0;
    if(!IntersectedPlane(vPoly, vLine,vNormal,originDistance))
		return false;
	Vector3 vIntersection = IntersectionPoint(vNormal, vLine, originDistance);//计算交点
	if(InsidePolygon(vIntersection, vPoly, verticeCount))//找到交点，判断是否在多边形内
		return true;						
	return false;								
}

int ClassifySphere(Vector3 &vCenter, 
				   Vector3 &vNormal, Vector3 &vPoint, float radius, float &distance)
{                                                              //球体与平面的关系
	float d = (float)PlaneDistance(vNormal, vPoint);

	
	distance = (vNormal.dotProduct(vCenter)+ d);

	if(Absolute(distance) < radius)   //绝对值小于半径，相交
		return INTERSECTS;
	else if(distance >= radius)       //大于或等于半径在前面   
		return FRONT;
	return BEHIND;
}

bool EdgeSphereCollision(Vector3 &vCenter, 
						 Vector3 vPolygon[], int vertexCount, float radius)//球体与多边形的边是否相交
{
	Vector3 vPoint;
	for(int i = 0; i < vertexCount; i++)
	{

	 vPoint = ClosestPointOnLine(vPolygon[i],     //返回当前边上离球心最近的点
		 vPolygon[(i + 1) % vertexCount], vCenter);
		float distance = Distance(vPoint, vCenter);//计算最近点与球心的距离
		if(distance < radius)
			return true;
	}
	return false;
}

bool SpherePolygonCollision(Vector3 vPolygon[], 
							Vector3 &vCenter, int vertexCount, float radius)
{
	Vector3 vNormal = Normal(vPolygon);
	float distance = 0.0f;                              //球体到平面的距离
	int classification = ClassifySphere(vCenter, vNormal, vPolygon[0], radius, distance);
	if(classification == INTERSECTS) 
	{
		Vector3 vOffset = vNormal * distance;            //投影球体中心到平面
		Vector3 vPosition = vCenter - vOffset;
		if(InsidePolygon(vPosition, vPolygon, 3))        //判断交点是否在多变形内
			return true;	
		else
		{

			if(EdgeSphereCollision(vCenter, vPolygon, vertexCount, radius)) //检查边
			{
				return true;	
			}
		}
	}
	return false;
}

Vector3 GetCollisionOffset(Vector3 &vNormal, float radius, float distance)
{
	Vector3 vOffset = Vector3(0, 0, 0);

	if(distance > 0)
	{
		float distanceOver = radius - distance;
		vOffset = vNormal * distanceOver;
	}
	else 
	{
		float distanceOver = radius + distance;
		vOffset = vNormal * -distanceOver;
	}

	return vOffset;
}

