#pragma once
class Player1;
class Terrain;
class SampleScene : public Scene
{
public:
	Player1* player;
	Mesh* tiger;

	Terrain* terrain;

public:
	SampleScene();
	~SampleScene();

	void Init();

	void Update();
	void Render();

};

