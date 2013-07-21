#include"CParticule.h"

bool CParticule::Init(int num)
{
	m_pnum = num;
	m_parlist = new tParticule[m_pnum];
	if(m_parlist == NULL)
		return false;
	return true;
}
void CParticule::Render()
{
}
void CParticule::Upadate()
{
}
CParticule::CParticule(): m_pnum(0),m_parlist(NULL)
{}
CParticule::~CParticule()
{
	if(m_parlist!=NULL)
	{
		delete[]m_parlist;
		m_parlist=NULL;
	}
}