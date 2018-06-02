#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::SetUpMatrix()
{
	auto device = D3DRenderer::GetInstance()->GetDevice();

	//���� ���
	D3DXMatrixIdentity(&matWorld);
	device->SetTransform(D3DTS_WORLD, &matWorld);

	//�� ���
	EyePt = D3DXVECTOR3(0.f, 0.f, -20.f);
	LookAtPt= D3DXVECTOR3(0.f, 0.f, 0.f);
	UpVec = D3DXVECTOR3(0.f, 1.f, 0.f);

	D3DXMatrixIdentity(&matView);
	D3DXMatrixLookAtLH(&matView, &EyePt, &LookAtPt, &UpVec);

	device->SetTransform(D3DTS_VIEW, &matView);

	//�������� ���
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1280.f/720.f, 1.f, 1000.f);
	device->SetTransform(D3DTS_PROJECTION, &matProj);

}
