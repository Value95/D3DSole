#ifndef TEXTURESTORE_H
#define TEXTURESTORE_H

#include "ResourceStore.h"
#include "Texture.h"

BEGIN(Engine)
class ENGINE_DLL CTextureStore final : public CResourceStore
{
	DECLARE_SINGLETON(CTextureStore)
private:
	typedef std::unordered_map<std::wstring, SHARED(_TexData)>	_TexDataMap;
	GETTOR(_TexDataMap, m_mCurSceneTextureData, {}, CurSceneTextureData);
	GETTOR(_TexDataMap, m_mStaticTextureData, {}, StaticTextureData);

public:
	void Awake(void) override;
	void Start(void) override;
	void OnDestroy(void) override;
		 
	void ClearCurResource(void) override;

	SHARED(_TexData) GetTextureData(std::wstring textureKey);
	void InitTextureForScene(std::wstring curScene);

private:
	void InitResource(std::wstring sourcePath) override;
	void ParsingTexture(std::wstring filePath, std::wstring fileName);

};
END

#endif