#pragma once
class FSM
{
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

