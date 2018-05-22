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
	m_Mesh = Mesh::Create("Resource/Mesh/tiger.x");
	AddChild(m_Mesh);
}

void Player1::Update()
{
	GameObject::Update();
}

void Player1::Render()
{
	GameObject::Render();
}
