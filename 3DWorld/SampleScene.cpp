#include "stdafx.h"
#include "SampleScene.h"
#include"Player1.h"
#include"Terrain.h"

SampleScene::SampleScene()
{
	player = new Player1();
	player->Init();
	terrain = new Terrain();
	terrain->Init();

	AddChild(terrain);

	Mesh2 = Mesh::Create("./Resource/Mesh/", "Tree01.x");
	Mesh2->m_Position.x = 10.f;
	Mesh2->SetScale(0.03f, 0.03f, 0.03f);

	AddChild(Mesh2);
	AddChild(player);
	AddChild(Camera::GetInstance());

	PlantingTreeRandom(1);
	Camera::GetInstance()->SetCameraThirdPerson(player);
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
