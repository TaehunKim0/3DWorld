#pragma once
class Director : public Singleton<Director>
{
private:
	Scene* m_CurrentScene;
	Scene* m_NextScene;

public:
	Director();
	virtual ~Director();

	void Update();
	void Render();

	void ChangeScene(Scene* scene);
};

