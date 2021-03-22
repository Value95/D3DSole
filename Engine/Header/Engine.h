#ifndef ENGINE_H
#define ENGINE_H

BEGIN(Engine)
class ENGINE_DLL CEngine abstract
{
protected:
	GETTOR(std::wstring, m_sectionKey, L"", SectionKey);
	GETTOR(std::wstring, m_objectKey, L"", ObjectKey);
public:
	explicit CEngine (void);
	virtual ~CEngine (void);

public:
	virtual	void Awake(void) PURE;
};
END
#endif