#include "stdafx.h"
#include "SampleScene.h"
#include"Player1.h"
#include"Terrain.h"
#include"WindMill.h"

SampleScene::SampleScene()
{
	player = new Player1();
	player->Init();

	terrain = new Terrain();
	terrain->Init();

	windmill = new WindMill();
	windmill->Init();
	windmill->m_Position.x = -5.f;
	
	AddChild(windmill);
	AddChild(terrain);

	Mesh2 = Mesh::Create("./Resource/Mesh/", "Tree01.x");
	Mesh2->m_Position.x = 20.f;
	Mesh2->SetScale(0.03f, 0.03f, 0.03f);
	player->m_fRadius = 1.f;
	Mesh2->m_fRadius = 2.f;

	
	AddChild(player);
	AddChild(Mesh2);
	AddChild(Camera::GetInstance());

	PlantingTreeRandom(1);
	Camera::GetInstance()->SetCameraFreeView();
}

SampleScene::~SampleScene()
{
}

void SampleScene::Init()
{
	
}

void SampleScene::Update()
{
	Scene::Update();

	printf("Scene 의 RotY : %f\n", m_RotY);

	D3DXVECTOR3 dt = player->m_Position - Mesh2->m_Position;
	D3DXVec3Normalize(&dt, &dt);

	
	//Mesh2->m_Position += dt * 0.05;

	//if (CollisionCheck(player, Mesh2))
	//{
	////	Mesh2->m_Active = false;

	//	


	//}

	//printf("X : %f\n", Input::GetInstance()->GetMousePosition().x);
	//printf("Delta : %f\n", Input::GetInstance()->GetDeltaMove().x);

}

void SampleScene::Render()
{
	Scene::Render();
}

void SampleScene::PlantingTreeRandom(int TreeNumber)
{
	int fMinX = -40;
	int fMaxX = 40;

	int fMinZ = -40;
	int fMaxZ = 40;

	Trees = new Mesh[TreeNumber];
	for (int i = 0; i < TreeNumber; i++)
	{
		Trees[i].Init("./Resource/Mesh/", "Tree01.x");
		Trees[i].SetScale(0.03f, 0.03f, 0.03f);

		AddChild(&Trees[i]);
	}

	for (int i = 0; i < TreeNumber; i++)
	{
		float x, z;

		x = (rand() % fMaxX) + fMinX;
		z = (rand() % fMaxZ) + fMinZ;

		Trees[i].SetPosition(x, 0, z);

	}

	/*
	나무 위치는 -50,50           50,50
				
	
				
				

			   -50,-50          50,-50
	*/
}

bool SampleScene::CollisionCheck(GameObject * obj1, GameObject * obj2)
{
	D3DXVECTOR3 v = obj2->m_Position - obj1->m_Position;
	float length = D3DXVec3Length(&v);

	float radius = obj1->m_fRadius + obj2->m_fRadius;

	if (radius > length)
	{
		for (DWORD i = 0; i < Mesh2->m_NumsMaterial; i++)
		{
			Mesh2->m_MeshMaterials[i].Ambient.a -= 0.1;
			Mesh2->m_MeshMaterials[i].Diffuse.a -= 0.1;
		}

		printf("충돌");
		return true;
	}

	return false;
}
