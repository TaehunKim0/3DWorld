#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
	: m_fRotX(0)
	, m_fRotY(0)
{
	EyePt = D3DXVECTOR3(0.f, 10.f, -30.f);
	LookAtPt = D3DXVECTOR3(0.f, 0.f, 0.f);
	UpVec = D3DXVECTOR3(0.f, 1.f, 0.f);
	m_Target = nullptr;

	
	//�������� ���
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1280.f / 720.f, 1.f, 1000.f);
	D3DRenderer::GetInstance()->GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	auto device = D3DRenderer::GetInstance()->GetDevice();

	//ī�޶� SRT ������ �ؾ���

	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matRotX;
	D3DXMATRIXA16 matRotY;
	D3DXVECTOR3 vLook; //������ �ٶ� ����

	if (Input::GetInstance()->GetKeyState(VK_RBUTTON) == KeyState::Pressed)
	{
		m_fRotX -= Input::GetInstance()->GetDeltaMove().x / 100;
		m_fRotY -= Input::GetInstance()->GetDeltaMove().y / 100;
	}

	D3DXMatrixRotationY(&matRotX, m_fRotX);
	D3DXMatrixRotationX(&matRotY, m_fRotY);

	matRot = matRotX * matRotY;
	D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0, 0, 1), &matRot);

	//D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0,0,1), &matRot); //ȸ���� ���� ������ vLook�� ����
	//D3DXVec3TransformNormal -> �� �Լ��� 3���� ���Ϳ� ����� ���̰� ���� ��ȯ�� (�̵� , ũ�� , ȸ��)�� ������ �� ����.
	//vLook �� ������ �ǹ��ϰ� �ȴ�.
	//D3DXVec3TransformCoord -> �� �Լ��� 3���� ���Ϳ� ����� ���ε� 3���� ���͸� 4���� ���ͷ� �ٲ� �� �������� 1 �� �� �̵��� ���� ��Ŵ
	//vLook �� ��ǥ ������ �ȴ�.

	//LookAtPt = EyePt + vLook;//������ �ٶ� ������ ����
				//�� �ڸ��� Ÿ���� ��ġ�� ������ ī�޶� �� Ÿ���� �ٶ�.

	if (m_Target)
	{
		LookAtPt = m_Target->m_Position;		// ī�޶�� �׻� Ÿ���� �ٶ󺻴�. (3��Ī ����)
		//EyePt = m_Target->m_Position + EyePt; // ������ �������� ȸ���� �������� Ÿ���� ������
	}

	printf("EyePt : %f\n", EyePt.x);

	if (Input::GetInstance()->GetKeyState('W') == KeyState::Pressed)
	{
		EyePt += vLook;
		LookAtPt += vLook;
	}
	if (Input::GetInstance()->GetKeyState('S') == KeyState::Pressed)
	{
		EyePt -= vLook;
		LookAtPt -= vLook;
	}
	if (Input::GetInstance()->GetKeyState('A') == KeyState::Pressed)
	{
		
	}
	if (Input::GetInstance()->GetKeyState('D') == KeyState::Pressed)
	{
		//LeftOrRight(1.f);
	}
	

	//���� ���
	D3DXMatrixIdentity(&matWorld);
	device->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXMatrixLookAtLH(&matView, &EyePt, &LookAtPt, &UpVec);
	device->SetTransform(D3DTS_VIEW, &matView);
}

void Camera::SetTarget(GameObject* ptarget)
{
	m_Target = ptarget;
}

void Camera::ForwardOrBackword(float fDelta)
{
	EyePt.z += fDelta;
	LookAtPt.z += fDelta;
}

void Camera::LeftOrRight(float fDelta)
{
	EyePt.x += fDelta;
	LookAtPt.x += fDelta;
}

void Camera::UpOrDown(float fDelta)
{
	EyePt.y += fDelta;
	LookAtPt.y += fDelta;
}
