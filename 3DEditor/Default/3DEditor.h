
// 3DEditor.h : 3DEditor ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy3DEditorApp:
// �� Ŭ������ ������ ���ؼ��� 3DEditor.cpp�� �����Ͻʽÿ�.
//

class CMy3DEditorApp : public CWinAppEx
{
public:
	CMy3DEditorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy3DEditorApp theApp;
