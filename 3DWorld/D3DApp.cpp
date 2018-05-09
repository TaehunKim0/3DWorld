#include "stdafx.h"
#include "D3DApp.h"


D3DApp::D3DApp()
{
}


D3DApp::~D3DApp()
{
}

bool D3DApp::Initialize(UINT width, UINT height, bool windowed)
{
	if (_CreateWindow() == false)
		return false;

	if (D3DRenderer::GetInstance()->Initialize(width, height, m_hWnd, windowed) == false)
		return false;

	return true;
}

bool D3DApp::_CreateWindow()
{
	return false;
}

void D3DApp::Release()
{
}

LRESULT D3DApp::WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	return LRESULT();
}
