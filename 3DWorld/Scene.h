#pragma once
class Scene : public GameObject
{
protected:
	Camera * m_Camera;

public:
	Scene();
	virtual ~Scene();

	void Update();
};

