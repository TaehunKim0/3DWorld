#pragma once
class Player1;
class Terrain;
class SampleScene : public Scene
{
public:
	Player1* player;
	Mesh* tiger;

	Terrain* terrain;
	Camera * m_Camera;
public:
	SampleScene();
	~SampleScene();

	void Init();

	void Update();
	void Render();

};

