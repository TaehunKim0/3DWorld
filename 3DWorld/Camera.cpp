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

	
	//프로젝션 행렬
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1280.f / 720.f, 1.f, 1000.f);
	D3DRenderer::GetInstance()->GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	auto device = D3DRenderer::GetInstance()->GetDevice();

	//카메라 SRT 순서로 해야함

	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matRotX;
	D3DXMATRIXA16 matRotY;
	D3DXVECTOR3 vLook; //눈에서 바라볼 방향

	if (Input::GetInstance()->GetKeyState(VK_RBUTTON) == KeyState::Pressed)
	{
		m_fRotX -= Input::GetInstance()->GetDeltaMove().x / 100;
		m_fRotY -= Input::GetInstance()->GetDeltaMove().y / 100;
	}

	D3DXMatrixRotationY(&matRotX, m_fRotX);
	D3DXMatrixRotationX(&matRotY, m_fRotY);

	matRot = matRotX * matRotY;
	D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0, 0, 1), &matRot);

	//D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0,0,1), &matRot); //회전한 곳의 방향을 vLook에 넣음
	//D3DXVec3TransformNormal -> 이 함수는 3차원 벡터와 행렬의 곱이고 여러 변환들 (이동 , 크기 , 회전)을 적용할 때 쓰임.
	//vLook 은 방향을 의미하게 된다.
	//D3DXVec3TransformCoord -> 이 함수도 3차원 벡터와 행렬의 곱인데 3차원 벡터를 4차원 벡터로 바꿀 때 마지막을 1 로 해 이동을 적용 시킴
	//vLook 은 좌표 개념이 된다.

	//LookAtPt = EyePt + vLook;//눈에서 바라볼 방향을 더함
				//이 자리에 타겟의 위치를 넣으면 카메라가 그 타겟을 바라봄.

	if (m_Target)
	{
		LookAtPt = m_Target->m_Position;		// 카메라는 항상 타겟을 바라본다. (3인칭 시점)
		//EyePt = m_Target->m_Position + EyePt; // 원점을 기준으로 회전이 끝났으면 타겟을 따라가자
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
	

	//월드 행렬
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
