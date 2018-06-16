#pragma once
class Player1;
class Terrain;
class WindMill;
class SampleScene : public Scene
{
public:
	Player1* player;
	Terrain* terrain;

	WindMill* windmill;

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

	bool CollisionCheck(GameObject* obj1, GameObject* obj2);


};

