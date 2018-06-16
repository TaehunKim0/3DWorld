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
	, m_fRadius(0.f)
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
	//Scale ����
	D3DXMatrixScaling(&matS, m_Scale.x, m_Scale.y, m_Scale.z);

	//Rotation ����
	D3DXMatrixRotationX(&matRotX, m_RotX); //X �� ������ ȸ�� ��Ʈ���� ����
	D3DXMatrixRotationY(&matRotY, m_RotY); //Y �� ������ ȸ�� ��Ʈ���� ����
	D3DXMatrixRotationZ(&matRotZ, m_RotZ); //Z �� ������ ȸ�� ��Ʈ���� ����
	D3DXMATRIX matR = matRotZ * matRotX * matRotY;

	//Translation ����
	D3DXMatrixTranslation(&matT, m_Position.x, m_Position.y, m_Position.z);

	//S * R * T
	m_wMatrix = matS * matR * matT;

	//�θ��� Matrix ���
	if (m_Parent && m_UseParentMatrix)
	{
		m_wMatrix *= m_Parent->m_wMatrix;
	}

	D3DRenderer::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &m_wMatrix);
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
		if(child->m_Active == true)
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
