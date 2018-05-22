#pragma once
class Player1 : public GameObject
{
private:
	Mesh* m_Mesh;


public:
	Player1();
	virtual ~Player1();

	void Init();

	void Update();
	void Render();

};

