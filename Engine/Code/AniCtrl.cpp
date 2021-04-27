#include "EngineStdafx.h"
#include "AniCtrl.h"

USING(Engine)

CAniCtrl::CAniCtrl(LPD3DXANIMATIONCONTROLLER pAniCtrl)
	: m_pAniCtrl(pAniCtrl)
	, m_iCurrentTrack(0)
	, m_iNewTrack(1)
	, m_fAccTime(0.f)
	, m_iOldAniIdx(99)	// ������ ���� ���� �ʰ� �ϱ� ���� ��
	, m_dPeriod(0.0)
{
	m_pAniCtrl->AddRef();
}

CAniCtrl::CAniCtrl(const CAniCtrl& rhs)
	: m_iCurrentTrack(rhs.m_iCurrentTrack)
	, m_iNewTrack(rhs.m_iNewTrack)
	, m_fAccTime(rhs.m_fAccTime)
	, m_iOldAniIdx(rhs.m_iOldAniIdx)
	, m_dPeriod(0.0)

{
	rhs.m_pAniCtrl->CloneAnimationController(rhs.m_pAniCtrl->GetMaxNumAnimationOutputs(),	// ���� �� ���� ��ü�� ���ϰ� �ִ� �ִ� �ִϸ��̼� ����
											rhs.m_pAniCtrl->GetMaxNumAnimationSets(),		// ���� ������ �ִϸ��̼� ����(��� 1������ ���� ��ġ)
											rhs.m_pAniCtrl->GetMaxNumTracks(),				// ����ϴ� �ִ� Ʈ���� ����(��� �ִ�� 2�� ���� ���)
											rhs.m_pAniCtrl->GetMaxNumEvents(),				// �޽� �ȿ� ����Ǵ� ���� ȿ��(�츮�� ��� ����)
											&m_pAniCtrl);
}


HRESULT CAniCtrl::Ready_AnimationCtrl(void)
{
	
	return S_OK;
}

void CAniCtrl::Set_AnimationSet(const _uint & iIndex)
{
	if (m_iOldAniIdx == iIndex)
		return;

	m_iNewTrack = (m_iCurrentTrack == 0 ? 1 : 0);

	LPD3DXANIMATIONSET	pAS = nullptr;

	m_pAniCtrl->GetAnimationSet(iIndex, &pAS);	

	m_dPeriod = pAS->GetPeriod() -1;	// ���� �ִϸ��̼� ���� ���� ��ü ��� �ð� ��ȯ

	////m_pAniCtrl->GetAnimationSetByName();
	m_pAniCtrl->SetTrackAnimationSet(m_iNewTrack, pAS);

	// ������� �ʰ� �ִ� �̺�Ʈ ������ ������ ���� ������ �ȵǴ� ��찡 �߻��ؼ� ȣ��
	m_pAniCtrl->UnkeyAllTrackEvents(m_iCurrentTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_iNewTrack);

	// ������ Ʈ���� ��� ������ �����ϴ� �Լ�, 3���� : �������� Ʈ���� ��� �Ǵ� ������ ������ ����
	m_pAniCtrl->KeyTrackEnable(m_iCurrentTrack, FALSE, m_fAccTime + 0.25);

	// Ʈ���� �����Ǵ� �ð����� ���� �ִϸ��̼� ���� � �ӵ��� �������� ����(�ӵ��� ��� ���� ���� 1)
	m_pAniCtrl->KeyTrackSpeed(m_iCurrentTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	// Ʈ���� �����Ǵ� �ð����� ���� �ִϸ��̼� ���� � ����ġ�� ���� �� ��(�ӵ��� ��� ���� ���� 1)
	m_pAniCtrl->KeyTrackWeight(m_iCurrentTrack, 0.1f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);
	
	// ���� ���� Ʈ�� Ȱ��ȭ�� ������ �Ǵ��ϴ� �Լ�
	m_pAniCtrl->SetTrackEnable(m_iNewTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_iNewTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_iNewTrack, 0.9f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->ResetTime(); // �ִϸ��̼��� ����Ǵ� �ð��� �ٽ� ����(advanced�Լ� ȣ�� �� ���������� �����Ǵ� �ð� ����)

	m_fAccTime = 0.f;

	m_pAniCtrl->SetTrackPosition(m_iNewTrack, 0.0);

	m_iOldAniIdx = iIndex;

	m_iCurrentTrack = m_iNewTrack;


}

void CAniCtrl::Play_Animation(const _double & fTimeDelta)
{
	// ù ��° ���� : ���� �ִϸ��̼��� �����ϴ� �Լ�,
	// �� ��° ���� : ��ü�� ���� ���峪 ����Ʈ�� ���� ó���� ����ϴ� ���ڰ�, ������ ����� ����.
	m_pAniCtrl->AdvanceTime(fTimeDelta * m_speed, NULL);

	m_fAccTime += fTimeDelta * m_speed;
}

_bool CAniCtrl::Is_AnimationSetEnd(void)
{
	D3DXTRACK_DESC		TrackInfo;
	ZeroMemory(&TrackInfo, sizeof(D3DXTRACK_DESC));

	m_pAniCtrl->GetTrackDesc(m_iCurrentTrack, &TrackInfo);

	if (TrackInfo.Position >= m_dPeriod)
		return true;

	return false;
}



CAniCtrl* CAniCtrl::Create(LPD3DXANIMATIONCONTROLLER pAniCtrl)
{
	CAniCtrl*	pInstance = new CAniCtrl(pAniCtrl);

	if (FAILED(pInstance->Ready_AnimationCtrl()))
		SafeRelease(pInstance);

	return pInstance;
}

CAniCtrl* CAniCtrl::Create(const CAniCtrl& rhs)
{
	CAniCtrl*	pInstance = new CAniCtrl(rhs);

	if (FAILED(pInstance->Ready_AnimationCtrl()))
		SafeRelease(pInstance);

	return pInstance;
}

void CAniCtrl::OnDestroy()
{
	SafeRelease(m_pAniCtrl);
}

_float CAniCtrl::CurentTime()
{
	D3DXTRACK_DESC		TrackInfo;
	ZeroMemory(&TrackInfo, sizeof(D3DXTRACK_DESC));

	m_pAniCtrl->GetTrackDesc(m_iCurrentTrack, &TrackInfo);

	_float percentage = TrackInfo.Position / m_dPeriod;
	return percentage;
}
