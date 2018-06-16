#include "stdafx.h"
#include "WindMill.h"

VERTEX windmillVertex[] = 
{
	{D3DXVECTOR3(0.f,5.f,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
	{D3DXVECTOR3(2.f,0.f,-2.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f)},
{ D3DXVECTOR3(-2.f,0.f,-2.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
{ D3DXVECTOR3(-2.f,0.f,2.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
{ D3DXVECTOR3(2.f,0.f,2.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
};

VERTEX windmillWingVertex[] =
{
	{ D3DXVECTOR3(-0.5f, 1.f ,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
{ D3DXVECTOR3(0.5f, 1.f ,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
{ D3DXVECTOR3(1.f, 0.5f ,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
{ D3DXVECTOR3(1.f, -0.5f ,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },

{ D3DXVECTOR3(0.5f, -1.f , 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
{ D3DXVECTOR3(-0.5f, -1.f , 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
{ D3DXVECTOR3(-1.f, -0.5f , 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
{ D3DXVECTOR3(-1.f, 0.5f, 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },

{ D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) }
};


WindMill::WindMill()
{

}


WindMill::~WindMill()
{
	m_pVB->Release();
	m_pIB->Release();
	m_pVBw->Release();
	m_pIBw->Release();
}


void WindMill::Init()
{
	if (FAILED(D3DRenderer::GetInstance()->GetDevice()->CreateVertexBuffer(4 * sizeof(VERTEX), 0, VertexFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
	{
		printf("xxxxx");
	}
	WingAngle = 0;

	VERTEX* vertex = nullptr;
	m_pVB->Lock(0, 0, (VOID**)&vertex, 0);

	memcpy(vertex, windmillVertex, sizeof(windmillVertex));

	m_pVB->Unlock();

	if (FAILED(D3DRenderer::GetInstance()->GetDevice()->CreateIndexBuffer(sizeof(INDEX) * 4, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIB, nullptr)))
	{
		printf("");
	}

	INDEX* index = nullptr;

	m_pIB->Lock(0, 0, (void**)&index, 0);
	index[0]._1 = 0;
	index[0]._2 = 1;
	index[0]._3 = 2;

	index[1]._1 = 0;
	index[1]._2 = 2;
	index[1]._3 = 3;

	index[2]._1 = 0;
	index[2]._2 = 3;
	index[2]._3 = 4;

	index[3]._1 = 0;
	index[3]._2 = 4;
	index[3]._3 = 1;

	m_pIB->Unlock();

	//


	if (FAILED(D3DRenderer::GetInstance()->GetDevice()->CreateVertexBuffer(9 * sizeof(VERTEX), 0, VertexFVF, D3DPOOL_MANAGED, &m_pVBw, nullptr)))
	{
		printf("xxxxx");
	}

	VERTEX* vertex2 = nullptr;
	m_pVBw->Lock(0, 0, (VOID**)&vertex2, 0);

	memcpy(vertex2, windmillWingVertex, sizeof(windmillWingVertex));

	m_pVBw->Unlock();

	if (FAILED(D3DRenderer::GetInstance()->GetDevice()->CreateIndexBuffer(sizeof(INDEX) * 4, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIBw, nullptr)))
	{
		printf("");
	}

	INDEX* index2 = nullptr;

	m_pIBw->Lock(0, 0, (void**)&index2, 0);
	index2[0]._1 = 8;
	index2[0]._2 = 0;
	index2[0]._3 = 1;

	index2[1]._1 = 8;
	index2[1]._2 = 2;
	index2[1]._3 = 3;

	index2[2]._1 = 8;
	index2[2]._2 = 5;
	index2[2]._3 = 4;

	index2[3]._1 = 8;
	index2[3]._2 = 7;
	index2[3]._3 = 6;

	m_pIBw->Unlock();
	
}

void WindMill::Update()
{
	D3DXVECTOR3 vDir(0, 0, -1);
	D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);
	D3DXVec3Normalize(&vDir, &vDir);

	if (Input::GetInstance()->GetKeyState('1') == KeyState::Up)
	{
		bWingShoot = true;
	}

	if (bWingShoot)
	{
		m_Position.z -= 1.f;

	}

	/*
	회전을 시키면 플레이어의 방향이 바뀌고
	그 방향으로 이동한다.

	*/

	printf("플레이어의 Rot Y : %f\n", m_RotY);

	float Speed = 0.5f;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_RotY -= 0.1f;

	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_RotY += 0.1f;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_Position = m_Position + vDir * Speed;
		Camera::GetInstance()->EyePt += vDir * Speed;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_Position = m_Position - vDir * Speed;
		Camera::GetInstance()->EyePt -= vDir * Speed;
	}

	GameObject::Update();

	WingAngle -= 1.0f;

	D3DXMATRIX mScale;
	D3DXMATRIX RotZ;
	D3DXMatrixScaling(&mScale, 2.f, 2.f, 2.f);
	D3DXMatrixTranslation(&m_wingTransform, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixRotationZ(&RotZ, D3DXToRadian(WingAngle));

	m_wingWorldTransform = mScale * RotZ * m_wingTransform;

}

void WindMill::Render()
{
	GameObject::Render();

	m_wingWorldTransform *= m_wMatrix;

	D3DRenderer::GetInstance()->GetDevice()->SetMaterial(&m_Mtrl);
	D3DRenderer::GetInstance()->GetDevice()->SetIndices(m_pIB);
	D3DRenderer::GetInstance()->GetDevice()->SetFVF(VertexFVF);
	D3DRenderer::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX));
	D3DRenderer::GetInstance()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 4);
	
	D3DRenderer::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &m_wingWorldTransform);

	D3DRenderer::GetInstance()->GetDevice()->SetMaterial(&m_Mtrl);
	D3DRenderer::GetInstance()->GetDevice()->SetIndices(m_pIBw);
	D3DRenderer::GetInstance()->GetDevice()->SetFVF(VertexFVF);
	D3DRenderer::GetInstance()->GetDevice()->SetStreamSource(0, m_pVBw, 0, sizeof(VERTEX));
	D3DRenderer::GetInstance()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 9, 0, 4);
	
}
