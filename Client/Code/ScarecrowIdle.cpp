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
	return NO_EVENT;
}

_uint CScarecrowIdle::Update()
{
	return NO_EVENT;
}

_uint CScarecrowIdle::LateUpdate()
{
	return NO_EVENT;
}

void CScarecrowIdle::OnDestroy(void)
{
}



