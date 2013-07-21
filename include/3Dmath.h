#ifndef _3DMATH_H_
#define _3DMATH_H_
#include"Vector.h"
#define PI 3.1415926535897932					

#define BEHIND		0
#define INTERSECTS	1
#define FRONT		2
//	返回法线向量或任意向量的长度
float Magnitude(Vector3 vNormal);
// 求空间中两点间的距离
float Distance(Vector3 vPoint1, Vector3 vPoint2);
Vector3 Normal(Vector3 vPolygon[])	;				//返回多边形的单位法向量
// 返回线vA-vB离vPoint最近的点
Vector3 ClosestPointOnLine(Vector3 vA, Vector3 vB, Vector3 vPoint);

// 返回平面到原点（0，0，0）的距离，参数为平面的法向量和平面任意一点
float PlaneDistance(Vector3 Normal, Vector3 Point);

//判断平面和线段的相交
bool IntersectedPlane(Vector3 vPoly[], Vector3 vLine[], Vector3 &vNormal, float &originDistance);
// 求两向量的夹角
double AngleBetweenVectors(Vector3 Vector1, Vector3 Vector2);

// 返回平面和线的交点
Vector3 IntersectionPoint(Vector3 vNormal, Vector3 vLine[], double distance);

//判断交点是否在多边形（矩形/三角形）内
bool InsidePolygon(Vector3 vIntersection, Vector3 Poly[], long verticeCount);

// 判断多边形与线段的碰撞
bool IntersectedPolygon(Vector3 vPoly[], Vector3 vLine[], int verticeCount);

// 返回平面与球体的关系（front behind intersects)
int ClassifySphere(Vector3 &vCenter, 
				   Vector3 &vNormal, Vector3 &vPoint, float radius, float &distance);

// 判断球体与多边形的边是否相交
bool EdgeSphereCollision(Vector3 &vCenter, 
						 Vector3 vPolygon[], int vertexCount, float radius);

// 判断球体与多边形是否相交
bool SpherePolygonCollision(Vector3 vPolygon[], 
							Vector3 &vCenter, int vertexCount, float radius);


// 返回球体要返回的向量，从而使它不与平面相交
Vector3 GetCollisionOffset(Vector3 &vNormal, float radius, float distance);

#endif 


