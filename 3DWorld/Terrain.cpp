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

DWORD VertexFVF = D3DFVF_XYZ | D3DFVF_TEX1;

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

	vertex[0].vPos = D3DXVECTOR3(-25.f, 0.f, 25.f);
	vertex[0].vUV = D3DXVECTOR2(0, 0);

	vertex[1].vPos = D3DXVECTOR3(25.f, 0.f, 25.f);
	vertex[1].vUV = D3DXVECTOR2(1, 0);

	vertex[2].vPos = D3DXVECTOR3(25.f, 0.f, -25.f);
	vertex[2].vUV = D3DXVECTOR2(1, 1);

	vertex[3].vPos = D3DXVECTOR3(-25.f, 0.f, 25.f);
	vertex[3].vUV = D3DXVECTOR2(0, 0);

	vertex[4].vPos = D3DXVECTOR3(25.f, 0.f, -25.f);
	vertex[4].vUV = D3DXVECTOR2(1, 1);

	vertex[5].vPos = D3DXVECTOR3(-25.f, 0.f, -25.f);
	vertex[5].vUV = D3DXVECTOR2(0, 1);


	m_pVB->Unlock();
}

void Terrain::Update()
{
	GameObject::Update();
}

void Terrain::Render()
{
	GameObject::Render();

	D3DRenderer::GetInstance()->GetDevice()->SetFVF(VertexFVF);
	D3DRenderer::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX));
	D3DRenderer::GetInstance()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}