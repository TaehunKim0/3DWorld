#include "stdafx.h"
#include "D3DRenderer.h"


D3DRenderer::D3DRenderer()
{
}

D3DRenderer::~D3DRenderer()
{
}

void D3DRenderer::Release()
{
	SafeRelease(m_D3D);
	SafeRelease(m_Device);
	SafeRelease(m_Vb);
}

bool D3DRenderer::Initialize(int width, int height, HWND hWnd, bool windowed)
{
	if (!(m_D3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return false;

	D3DPRESENT_PARAMETERS pp = {};
	pp.AutoDepthStencilFormat = D3DFMT_D16;
	pp.BackBufferWidth = width;
	pp.BackBufferHeight = height;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.Windowed = !windowed;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.EnableAutoDepthStencil = true;

	HRESULT hr = m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &m_Device);

	if FAILED(hr)
		return false;

	m_Device->SetRenderState(D3DRS_ZENABLE, true);
	m_Device->SetRenderState(D3DRS_LIGHTING, true);
	m_Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	//
	D3DLIGHT9 Light;
	ZeroMemory(&Light, sizeof(D3DLIGHT9));

	Light.Type = D3DLIGHT_DIRECTIONAL;

	Light.Direction = D3DXVECTOR3(1.f,1.f,1.f);

	Light.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f); //³­¹Ý»ç±¤
	Light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.f); //ÁÖº¯±¤
	Light.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f); //Á¤¹Ý»ç±¤
	
	

	m_Device->SetLight(0, &Light);
	m_Device->LightEnable(0, true);

	

	return true;
}

void D3DRenderer::RenderBegin()
{
	m_Device->BeginScene();
	m_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 125, 125), 1.f, 0.f);
}

void D3DRenderer::RenderEnd()
{
	m_Device->EndScene();
	m_Device->Present(NULL, NULL, NULL, NULL);
}
