#pragma once
class FSM
{
protected:
	GETTOR_SETTOR(CPlayer*, m_player, {}, Player);

public:
	FSM();
	~FSM();
public:
	virtual void Start() PURE;
	virtual void End() PURE;

	virtual _uint FixedUpdate() PURE;
	virtual _uint Update()	PURE;
	virtual _uint LateUpdate() PURE;

	virtual void OnDestroy(void) PURE;
};

