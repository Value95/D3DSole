#include "EngineStdafx.h"
#include "AniCtrl.h"

USING(Engine)

CAniCtrl::CAniCtrl(LPD3DXANIMATIONCONTROLLER pAniCtrl)
	: m_pAniCtrl(pAniCtrl)
	, m_iCurrentTrack(0)
	, m_iNewTrack(1)
	, m_fAccTime(0.f)
	, m_iOldAniIdx(99)	// 쓰레기 값이 들어가지 않게 하기 위한 값
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
	rhs.m_pAniCtrl->CloneAnimationController(rhs.m_pAniCtrl->GetMaxNumAnimationOutputs(),	// 복제 시 원본 객체가 지니고 있는 최대 애니메이션 갯수
											rhs.m_pAniCtrl->GetMaxNumAnimationSets(),		// 구동 가능한 애니메이션 갯수(대게 1인자의 값과 일치)
											rhs.m_pAniCtrl->GetMaxNumTracks(),				// 사용하는 최대 트랙의 갯수(대게 최대로 2개 정도 사용)
											rhs.m_pAniCtrl->GetMaxNumEvents(),				// 메쉬 안에 적용되는 각종 효과(우리는 사용 못함)
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

	m_dPeriod = pAS->GetPeriod() -1;	// 현재 애니메이션 셋이 지닌 전체 재생 시간 반환

	////m_pAniCtrl->GetAnimationSetByName();
	m_pAniCtrl->SetTrackAnimationSet(m_iNewTrack, pAS);

	// 사용하지 않고 있는 이벤트 정보들 때문에 선형 보간이 안되는 경우가 발생해서 호출
	m_pAniCtrl->UnkeyAllTrackEvents(m_iCurrentTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_iNewTrack);

	// 지정한 트랙의 사용 유무를 결정하는 함수, 3인자 : 언제부터 트랙을 사용 또는 해제할 것인지 결정
	m_pAniCtrl->KeyTrackEnable(m_iCurrentTrack, FALSE, m_fAccTime + 0.25);

	// 트랙이 해제되는 시간동안 현재 애니메이션 셋은 어떤 속도로 움직일지 결정(속도의 상수 값은 각자 1)
	m_pAniCtrl->KeyTrackSpeed(m_iCurrentTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	// 트랙이 해제되는 시간동안 현재 애니메이션 셋은 어떤 가중치를 갖게 할 지(속도의 상수 값은 각자 1)
	m_pAniCtrl->KeyTrackWeight(m_iCurrentTrack, 0.1f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);
	
	// 새로 들어온 트랙 활성화의 유무를 판단하는 함수
	m_pAniCtrl->SetTrackEnable(m_iNewTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_iNewTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_iNewTrack, 0.9f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->ResetTime(); // 애니메이션이 재생되던 시간을 다시 세팅(advanced함수 호출 시 내부적으로 누적되던 시간 리셋)

	m_fAccTime = 0.f;

	m_pAniCtrl->SetTrackPosition(m_iNewTrack, 0.0);

	m_iOldAniIdx = iIndex;

	m_iCurrentTrack = m_iNewTrack;


}

void CAniCtrl::Play_Animation(const _double & fTimeDelta)
{
	// 첫 번째 인자 : 실제 애니메이션을 구동하는 함수,
	// 두 번째 인자 : 객체가 지닌 사운드나 이펙트에 대한 처리를 담당하는 인자값, 느려서 사용을 안함.
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
