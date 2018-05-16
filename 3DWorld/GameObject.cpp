#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Update()
{
	
}

void GameObject::Render()
{
	
}

void GameObject::AddChild(GameObject * child)
{
	if (child == nullptr)
		return;

	m_Children.push_back(child);
	child->m_Parent = this;
}

void GameObject::RemoveChild(GameObject * child)
{
}
