#include "stdafx.h"
#include "ScarecrowIdle.h"
#include "Monster.h"

CScarecrowIdle::CScarecrowIdle(CMonster* monster)
{
	m_monster = monster;
}

CScarecrowIdle::~CScarecrowIdle()
{
}

void CScarecrowIdle::Start()
{
	if (!init)
	{
		init = true;
	}
}

void CScarecrowIdle::End()
{
}

_uint CScarecrowIdle::FixedUpdate()
{
	return _uint();
}

_uint CScarecrowIdle::Update()
{
	return _uint();
}

_uint CScarecrowIdle::LateUpdate()
{
	return _uint();
}

void CScarecrowIdle::OnDestroy(void)
{
}



