#pragma once
class Player1;
class SampleScene : public Scene
{
public:
	Player1* player;


public:
	SampleScene();
	~SampleScene();

	void Init();

	void Update();
	void Render();

};

