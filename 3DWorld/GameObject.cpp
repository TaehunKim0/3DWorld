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
}


GameObject::~GameObject()
{
}

void GameObject::SetMatrix()
{
	D3DXMATRIXA16 matS; //������ ��Ʈ����
	D3DXMATRIXA16 matR; //ȸ�� ��Ʈ����
	D3DXMATRIXA16 matT; //�̵� ��Ʈ����

	D3DXMatrixRotationX(&matR, m_RotX); //X �� ������ ȸ�� ��Ʈ���� ����
	D3DXMatrixRotationY(&matR, m_RotY); //Y �� ������ ȸ�� ��Ʈ���� ����
	D3DXMatrixRotationZ(&matR, m_RotZ); //Z �� ������ ȸ�� ��Ʈ���� ����

	D3DXMatrixTranslation(&matT, m_Position.x, m_Position.y, m_Position.z);

	m_wMatrix = matR * matT;

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
