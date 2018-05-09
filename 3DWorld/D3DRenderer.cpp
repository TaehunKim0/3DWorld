#include "stdafx.h"
#include "D3DRenderer.h"


D3DRenderer::D3DRenderer()
{
}

D3DRenderer::~D3DRenderer()
{
}

bool D3DRenderer::Initialize(int width, int height, HWND hWnd, bool windowed)
{
	if (m_D3D == Direct3DCreate9(D3D_SDK_VERSION) == false)
		return false;

	




	return false;
}

void D3DRenderer::RenderBegin()
{
}

void D3DRenderer::RenderEnd()
{
}
