#pragma once
class Player1;
class Terrain;
class SampleScene : public Scene
{
public:
	Player1* player;
	Terrain* terrain;

	Mesh* tiger;
	Mesh* Mesh2;
	Mesh* Trees;

public:
	SampleScene();
	~SampleScene();

	void Init();

	void Update();
	void Render();

	void PlantingTreeRandom(int TreeNumber);

};

