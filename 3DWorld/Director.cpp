#include "stdafx.h"
#include "Director.h"


Director::Director()
	: m_CurrentScene(nullptr)
	, m_NextScene(nullptr)
{
}

Director::~Director()
{
}

void Director::Update()
{
	m_CurrentScene->Update();
}

void Director::Render()
{
	m_CurrentScene->Render();
}

void Director::ChangeScene(Scene * scene)
{
	if (m_CurrentScene)
		SafeDelete(m_CurrentScene);

	m_CurrentScene = scene;
}
