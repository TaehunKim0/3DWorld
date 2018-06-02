#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	m_Camera = new Camera();
	AddChild(m_Camera);
}

Scene::~Scene()
{
}

void Scene::Update()
{
	GameObject::Update();
}

