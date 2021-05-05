#pragma once
class MonsterFSM
{
private:
	GETTOR_SETTOR(CMonster*, m_monster, {}, Monster);
public:
	MonsterFSM();
	~MonsterFSM();
public:
	virtual void Start() PURE;
	virtual void End() PURE;

	virtual _uint FixedUpdate() PURE;
	virtual _uint Update()	PURE;
	virtual _uint LateUpdate() PURE;

	virtual void OnDestroy(void) PURE;
};

