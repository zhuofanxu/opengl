#ifndef _CPARTICULE_H_
#define _CPARTICULE_H_
#include"Vector.h"
struct tParticule{
	Vector3    m_pos;              // 位置
	Vector3    m_velocity;               //速度
	Vector3    m_acceleration;          //加速度
	float      m_lifetime;             //生命值
	float      m_dec;                     //消失的速率
	float      m_size;                  //尺寸
	float      m_color[3];              //颜色
};
class CParticule
{
public:
	CParticule();
	virtual bool Init(int num);
	virtual void Upadate();
	virtual void Render();
	virtual ~CParticule();
protected:
	tParticule *m_parlist;                 //粒子指针
	int        m_pnum;                   //粒子数目
};
#endif       _CPARTICULE_H_