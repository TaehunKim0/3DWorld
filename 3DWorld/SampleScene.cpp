#include "stdafx.h"
#include "SampleScene.h"
#include"Player1.h"
#include"Terrain.h"

SampleScene::SampleScene()
{
	player = new Player1();
	player->Init();

	AddChild(player);

	terrain = new Terrain();
	terrain->Init();

	AddChild(terrain);
	
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

	printf("X : %f\n", Input::GetInstance()->GetMousePosition().x);


	//printf("Delta : %f\n", Input::GetInstance()->GetDeltaMove().x);

}

void SampleScene::Render()
{
	Scene::Render();
}
