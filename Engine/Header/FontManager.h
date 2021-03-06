#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CFontManager final : public CEngine
{
	DECLARE_SINGLETON(CFontManager)
public:
	void		Awake(void) override;
	void		Start(void);

	_uint		PreRender(void);
	_uint		Render(void);
	_uint		PostRender(void);

	void		OnDestroy(void);

	void		AddText(std::wstring textKey, std::wstring msg,
		D3DXVECTOR3 position, D3DXCOLOR color);
	void		RewriteText(std::wstring textKey, std::wstring msg);
	void		DeleteText(std::wstring textKey);
	void		DrawMyText(_Text* pText);
private:
	std::unordered_map<std::wstring, _Text*>	m_mTexts;
	LPD3DXFONT	m_pFont;

};
END
#endif	