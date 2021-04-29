#ifndef SHADERSTORE_H
#define SHADERSTORE_H

#include "ResourceStore.h"

BEGIN(Engine)
class ENGINE_DLL CShaderStore final : public CResourceStore
{
	DECLARE_SINGLETON(CShaderStore)
private:
	typedef std::unordered_map<std::wstring, LPD3DXEFFECT*>	_MeshDataMap;
	GETTOR(_MeshDataMap, m_mCurSceneShaderData, {}, CurSceneShaderData);
	GETTOR(_MeshDataMap, m_StaticShaderData, {}, StaticShaderData)

public:
	void Awake(void) override;
	void Start(void) override;
	void OnDestroy(void) override;
		  
	void ClearCurResource(void) override;
		  
	LPD3DXEFFECT* GetShaderData(std::wstring meshKey);
	void InitShaderForScene(std::wstring curScene);
private:
	void InitResource(std::wstring sourcePath) override;
	void ParsingMesh(std::wstring filePath, std::wstring fileName);

};
END
#endif // !SHADERSTORE_H
