#include "stdafx.h"
#include "ScarecrowMaintenance.h"

CScarecrowMaintenance::CScarecrowMaintenance(CMonster* monster)
{
	m_monster = monster;
}

CScarecrowMaintenance::~CScarecrowMaintenance()
{
}

void CScarecrowMaintenance::Start()
{

}

void CScarecrowMaintenance::End()
{
}

_uint CScarecrowMaintenance::FixedUpdate()
{
	return NO_EVENT;
}

_uint CScarecrowMaintenance::Update()
{


	return NO_EVENT;
}

_uint CScarecrowMaintenance::LateUpdate()
{
	return NO_EVENT;
}

void CScarecrowMaintenance::OnDestroy(void)
{
}



