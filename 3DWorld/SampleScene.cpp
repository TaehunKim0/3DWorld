#include "stdafx.h"
#include "SampleScene.h"
#include"Player1.h"

SampleScene::SampleScene()
{
	player = new Player1();
	player->Init();

	AddChild(player);

	
}

SampleScene::~SampleScene()
{
}

void SampleScene::Init()
{
	
}

void SampleScene::Update()
{
	GameObject::Update();

}

void SampleScene::Render()
{
	Scene::SetUpMatrix();

	GameObject::Render();
}
