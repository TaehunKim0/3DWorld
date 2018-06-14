#include "stdafx.h"
#include "Terrain.h"


VERTEX g_TerrainVertex[] = {
	{ D3DXVECTOR3(-25.f, 0.f, 25.f), D3DXVECTOR2(0,0) },
{ D3DXVECTOR3(25.f, 0.f, 25.f), D3DXVECTOR2(1,0) },
{ D3DXVECTOR3(25.f, 0.f, -25.f), D3DXVECTOR2(1,1) },

{ D3DXVECTOR3(-25.f, 0.f, 25.f), D3DXVECTOR2(0,0) },
{ D3DXVECTOR3(25.f, 0.f, -25.f), D3DXVECTOR2(1,1) },
{ D3DXVECTOR3(-25.f, 0.f, -25.f), D3DXVECTOR2(0,1) }
};

DWORD VertexFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

Terrain::Terrain()
{
}


Terrain::~Terrain()
{
}

void Terrain::Init()
{
	if FAILED(D3DRenderer::GetInstance()->GetDevice()->CreateVertexBuffer(6 * sizeof(VERTEX), 0, VertexFVF, D3DPOOL_MANAGED, &m_pVB, nullptr))
	{
		printf("xxxxx");
	}

	VERTEX* vertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&vertex, 0);

	vertex[0].vPos = D3DXVECTOR3(-50.f, 0.f, 50.f);
	vertex[0].Diffuse = D3DXCOLOR(1, 1, 1, 1);
	//vertex[0].vNormal = D3DXVECTOR3(0,1,0);

	vertex[1].vPos = D3DXVECTOR3(50.f, 0.f, 50.f);
	vertex[1].Diffuse = D3DXCOLOR(1, 1, 1, 1);
	//vertex[1].vNormal = D3DXVECTOR3(0, 1, 0); //*D3DXVec3Normalize(&D3DXVECTOR3(), &D3DXVECTOR3(-1, 1, -1));

	vertex[2].vPos = D3DXVECTOR3(50.f, 0.f, -50.f);
	vertex[2].Diffuse = D3DXCOLOR(1, 1, 1, 1);
	//vertex[2].vNormal = D3DXVECTOR3(0, 1, 0);

	vertex[3].vPos = D3DXVECTOR3(-50.f, 0.f, 50.f);
	vertex[3].Diffuse = D3DXCOLOR(1, 1, 1, 1);
	//vertex[3].vNormal = D3DXVECTOR3(0, 1, 0);

	vertex[4].vPos = D3DXVECTOR3(50.f, 0.f, -50.f);
	vertex[4].Diffuse = D3DXCOLOR(1, 1, 1, 1);
	//vertex[4].vNormal = D3DXVECTOR3(0, 1, 0);

	vertex[5].vPos = D3DXVECTOR3(-50.f, 0.f, -50.f);
	vertex[5].Diffuse = D3DXCOLOR(1, 1, 1, 1);
	//vertex[5].vNormal = D3DXVECTOR3(0, 1, 0);


	m_pVB->Unlock();
}

void Terrain::Update()
{
	GameObject::Update();

	//printf("m_RotY : %f\n", m_RotY);

}

void Terrain::Render()
{
	GameObject::Render();

	D3DRenderer::GetInstance()->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DRenderer::GetInstance()->GetDevice()->SetFVF(VertexFVF);
	D3DRenderer::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX));
	D3DRenderer::GetInstance()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	D3DRenderer::GetInstance()->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
}