#include "stdafx.h"
#include "Player1.h"


Player1::Player1()
{
}

Player1::~Player1()
{
}

void Player1::Init()
{
	m_Mesh = Mesh::Create("./Resource/Mesh/", "TombStone.x");


	AddChild(m_Mesh);
}

void Player1::Update()
{
	GameObject::Update();

	D3DXVECTOR3 vDir(0, 0, 1);
	D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);
	D3DXVec3Normalize(&vDir, &vDir);

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

	if (GetAsyncKeyState('R') & 0x8000)
	{
		m_RotY += 0.1f;
	}
}

void Player1::Render()
{
	GameObject::Render();
}
