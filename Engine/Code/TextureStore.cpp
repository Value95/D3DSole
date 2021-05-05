#include "EngineStdafx.h"
#include "TextureStore.h"
#include "DeviceManager.h"


USING(Engine)
IMPLEMENT_SINGLETON(CTextureStore)

void CTextureStore::Awake(void)
{
	__super::Awake();
	m_fpResourceHandler = std::bind(&CTextureStore::ParsingTexture, this, std::placeholders::_1, std::placeholders::_2);
	m_resourcePath = L"..\\..\\Resource\\Texture";
}

void CTextureStore::Start(void)
{
	__super::Start();
}

void CTextureStore::OnDestroy(void)
{
	m_mCurSceneTextureData.clear();
	m_mStaticTextureData.clear();
}

void CTextureStore::ClearCurResource(void)
{
	m_mCurSceneTextureData.clear();
}

SHARED(_TexData) CTextureStore::GetTextureData(std::wstring textureKey)
{
	auto iter_find_static = m_mStaticTextureData.find(textureKey);
	if (iter_find_static != m_mStaticTextureData.end())
		return iter_find_static->second;
		
	auto iter_find_cur = m_mCurSceneTextureData.find(textureKey);
	if (iter_find_cur != m_mCurSceneTextureData.end())
		return iter_find_cur->second;

	MSG_BOX(__FILE__, (L"There is no textureKey : [" + textureKey + L"] in GetTextureData").c_str());
	return nullptr;
}

IDirect3DBaseTexture9 * CTextureStore::GetSkyTextureData(std::wstring skyTextureKey)
{
	auto iter_find_static = m_skyTextureData.find(skyTextureKey);
	if (iter_find_static != m_skyTextureData.end())
		return iter_find_static->second;

	return nullptr;
}

void CTextureStore::InitTextureForScene(std::wstring curScene)
{
	InitResource(m_resourcePath + L"\\" + curScene);
}

void CTextureStore::InitResource(std::wstring sourcePath)
{
	__super::InitResource(sourcePath);
}

void CTextureStore::ParsingTexture(std::wstring filePath, std::wstring fileName)
{
	SHARED(_TexData) pNewTex(new _TexData);
	std::wstring texKey = RemoveExtension(fileName);
	std::wstring fullPath = filePath + L"\\" + fileName;

	_TexDataMap* pCurMap = nullptr;
	if (m_isStatic)
		pCurMap = &m_mStaticTextureData;
	else
		pCurMap = &m_mCurSceneTextureData;

	auto& iter_Find = pCurMap->find(texKey);

	if (pCurMap->end() == iter_Find) // texturKey가 중첩으로 들어가는것을 방지
	{
		CString extension = PathFindExtension(fileName.c_str());
		
		CString dds = ".dds";
		CString tga = ".tga";
		CString png = ".png";
		if (!extension.Compare(dds))
		{
			HRESULT hr;
			IDirect3DBaseTexture9* texture = nullptr;

			hr = D3DXCreateCubeTextureFromFile(GET_DEVICE, fullPath.c_str(), (LPDIRECT3DCUBETEXTURE9*)&texture);
			m_skyTextureData.insert(pair<std::wstring, IDirect3DBaseTexture9*>(texKey, texture));
			
		}
		else if (!extension.Compare(png) || !extension.Compare(tga))
		{
			if (FAILED(D3DXGetImageInfoFromFile(fullPath.c_str(), &pNewTex->imageInfo)))
				MSG_BOX(__FILE__, (L"TexKey : [" + texKey + L"] get image info failed in ParsingTexture").c_str());
			if (FAILED(D3DXCreateTextureFromFileEx(GET_DEVICE,
				fullPath.c_str(),
				pNewTex->imageInfo.Width,
				pNewTex->imageInfo.Height,
				pNewTex->imageInfo.MipLevels,
				0,
				pNewTex->imageInfo.Format,
				D3DPOOL_MANAGED,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				0,
				nullptr,
				nullptr,
				&pNewTex->pTexture)))
				MSG_BOX(__FILE__, (L"TexKey : [" + texKey + L"] create texture failed in ParsingTexture").c_str());

			pNewTex->name = texKey;
			(*pCurMap)[texKey] = pNewTex;
		}
	}
	else
		MSG_BOX(__FILE__, (L"TexKey : [" + texKey + L"] is already there").c_str());
}
