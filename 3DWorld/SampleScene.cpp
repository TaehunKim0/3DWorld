#include "stdafx.h"
#include "SampleScene.h"


SampleScene::SampleScene()
{
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
