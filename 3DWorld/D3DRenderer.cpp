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
}

bool D3DRenderer::Initialize(int width, int height, HWND hWnd, bool windowed)
{
	m_bWireFrame = false;

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

	if (FAILED(hr))
		return false;

	m_Device->SetRenderState(D3DRS_ZENABLE, true);
	m_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_Device->SetRenderState(D3DRS_LIGHTING, true);
	m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //�ؽ��İ� ���� ���� �״�� ��
	m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //�ؽ��İ� ���� ���ĸ� 1 - srcalpha

	m_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); //�ָ� �ִ� �ؽ��� ���
	m_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); //������ �ִ� �ؽ��� Ȯ��
	m_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); //�ڿ������� ����

	//���ĺ��� �Ҷ��� ���ĺ��� �����ʴ� ��ü�� �׸���, ���� �ָ� �ִ� �ͺ��� ������ �ִ� ��ü���� �׸��� (�� ����).

	//m_Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	

	//
	D3DLIGHT9 Light;
	ZeroMemory(&Light, sizeof(D3DLIGHT9));

	Light.Type = D3DLIGHT_DIRECTIONAL;

	Light.Direction = D3DXVECTOR3(1.f,-1.f,1.f);

	Light.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f); //���ݻ籤 (�ټ��� �������� �ݻ��)
	Light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.f); //�ֺ��� (Ư���� ������� �ֺ��� ���� �ִ� ��)
	Light.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f); //���ݻ籤 (�� �������θ� �ݻ�Ǵ� ��)

	m_Device->SetLight(0, &Light);
	m_Device->LightEnable(0, true);

	return true;
}

void D3DRenderer::RenderBegin()
{
	if (m_bWireFrame)
	{
		m_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		m_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	if (Input::GetInstance()->GetKeyState(VK_SPACE) == KeyState::Up)
	{
		m_bWireFrame ^= true;
	}

	m_Device->BeginScene();
	m_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 125, 125), 1.f, 0.f);
}

void D3DRenderer::RenderEnd()
{
	m_Device->EndScene();
	m_Device->Present(NULL, NULL, NULL, NULL);
}
