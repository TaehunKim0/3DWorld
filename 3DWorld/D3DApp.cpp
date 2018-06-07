#include "stdafx.h"
#include "D3DApp.h"
#include"SampleScene.h"

D3DApp::D3DApp()
{
}


D3DApp::~D3DApp()
{
}

bool D3DApp::Initialize(UINT width, UINT height, bool windowed)
{
	m_WindowWidth = width;
	m_WindowHeight = height;

	m_fOldTime = GetTickCount();
	m_fCurTime = 0.f;
	m_fDeltaTime = 0.f;

	if (_CreateWindow() == false)
		return false;

	if (D3DRenderer::GetInstance()->Initialize(width, height, m_hWnd, windowed) == false)
		return false;

	Director::GetInstance()->ChangeScene(new SampleScene());

	return true;
}

bool D3DApp::_CreateWindow()
{	
	WNDCLASS wc = {};
	wc.lpszClassName = "WalkingDead";
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClass(&wc))
		return false;

	HWND handle = CreateWindow("WalkingDead", "WalkingDead", WS_OVERLAPPEDWINDOW, 0, 0, m_WindowWidth,m_WindowHeight, NULL, NULL, NULL, NULL);

	if (!handle)
		return false;

	m_hWnd = handle;

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);
	

	return true;
}

void D3DApp::Release()
{
	D3DRenderer::GetInstance()->Release();
}

void D3DApp::RunGame()
{
	MSG msg;
	msg = {};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			m_fCurTime = GetTickCount();
			m_fDeltaTime = (m_fCurTime - m_fOldTime) / 1000.f;

			m_fOldTime = m_fCurTime;

			Input::GetInstance()->Update();
			D3DRenderer::GetInstance()->RenderBegin();
			Director::GetInstance()->Update();
			Director::GetInstance()->Render();
			D3DRenderer::GetInstance()->RenderEnd();
		}

	}
}

LRESULT D3DApp::WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, w, l);
}
