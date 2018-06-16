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

	

	if (GetAsyncKeyState('R') & 0x8000)
	{
		m_RotY += 0.1f;
	}
}

void Player1::Render()
{
	GameObject::Render();
}
