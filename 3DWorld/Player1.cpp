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

	printf("플레이어의 Rot Y : %f\n", m_RotY);

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_Position.x -= 0.1f;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_Position.x += 0.1f;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_Position.z += 0.1f;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_Position.z -= 0.1f;
}

void Player1::Render()
{
	GameObject::Render();
}
