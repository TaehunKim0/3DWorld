#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
	: m_fRotX(0)
	, m_fRotY(0)
{
	EyePt = D3DXVECTOR3(0.f, 10.f, -30.f);
	LookAtPt = D3DXVECTOR3(0.f, 0.f, 0.f);
	UpVec = D3DXVECTOR3(0.f, 1.f, 0.f);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	auto device = D3DRenderer::GetInstance()->GetDevice();

	//월드 행렬
	D3DXMatrixIdentity(&matWorld);
	device->SetTransform(D3DTS_WORLD, &matWorld);

	float delta = D3DApp::GetInstance()->GetDeltaTime();

	D3DXMATRIXA16 matRot;

	D3DXMATRIXA16 matRotX;
	D3DXMATRIXA16 matRotY;
	
	if (Input::GetInstance()->GetKeyState(VK_RBUTTON) == KeyState::Pressed)
	{
		m_fRotX -= Input::GetInstance()->GetDeltaMove().x * 0.005;
		m_fRotY -= Input::GetInstance()->GetDeltaMove().y * 0.005;
	}

	D3DXMatrixRotationY(&matRotX, m_fRotX);
	D3DXMatrixRotationX(&matRotY, m_fRotY);

	matRot = matRotX * matRotY;

	D3DXVECTOR3 vLook; //눈에서 바라볼 방향

	D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0, 0, 1), &matRot);

	LookAtPt = EyePt + vLook; //눈에서 바라볼 방향을 더함
				//이 자리에 타겟의 위치를 넣으면 카메라가 그 타겟을 바라봄.

	if (Input::GetInstance()->GetKeyState(VK_UP) == KeyState::Pressed)
	{
		EyePt += vLook;
		LookAtPt += vLook;
	}
	if (Input::GetInstance()->GetKeyState(VK_DOWN) == KeyState::Pressed)
	{
		EyePt -= vLook;
		LookAtPt -= vLook;
	}

	//printf("EyePt Z : %f\n", EyePt.z);

	D3DXMatrixLookAtLH(&matView, &EyePt, &LookAtPt, &UpVec);

	device->SetTransform(D3DTS_VIEW, &matView);

	//프로젝션 행렬
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1280.f / 720.f, 1.f, 1000.f);
	device->SetTransform(D3DTS_PROJECTION, &matProj);




}
