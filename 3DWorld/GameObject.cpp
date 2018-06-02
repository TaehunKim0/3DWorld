#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
	: m_Active(true)
	, m_Name("")
	, m_Parent(nullptr)
	, m_Position(0.f,0.f,0.f)
	, m_Rotation(0.f,0.f,0.f)
	, m_RotX(0.f)
	, m_RotY(0.f)
	, m_RotZ(0.f)
	, m_Scale(1.f,1.f,1.f)
	, m_Size(0.f,0.f,0.f)
	, m_UseParentMatrix(1)
{
	D3DXMatrixIdentity(&m_wMatrix);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matRotX);
	D3DXMatrixIdentity(&matRotY);
	D3DXMatrixIdentity(&matRotZ);
	D3DXMatrixIdentity(&matT);
}

GameObject::~GameObject()
{
}

void GameObject::SetMatrix()
{
	D3DXMatrixRotationX(&matRotX, m_RotX); //X 축 방향의 회전 매트릭스 설정
	D3DXMatrixRotationY(&matRotY, m_RotY); //Y 축 방향의 회전 매트릭스 설정
	D3DXMatrixRotationZ(&matRotZ, m_RotZ); //Z 축 방향의 회전 매트릭스 설정

	D3DXMatrixTranslation(&matT, m_Position.x, m_Position.y, m_Position.z);

	m_wMatrix = matS* matRotX * matRotY * matRotZ * matT;

	if (m_Parent && m_UseParentMatrix)
	{
		m_wMatrix *= m_Parent->m_wMatrix;
	}

}

void GameObject::Update()
{
	if (m_Active == false)
		return;

	for (auto child : m_Children)
	{
		child->Update();
	}
}

void GameObject::Render()
{
	if (m_Active == false)
		return;

	SetMatrix();

	for (auto child : m_Children)
	{
		child->Render();
	}
}

void GameObject::AddChild(GameObject * child)
{
	if (child == nullptr)
		return;

	m_Children.push_back(child);
	child->m_Parent = this;
}

void GameObject::RemoveChild(GameObject * child)
{
}
