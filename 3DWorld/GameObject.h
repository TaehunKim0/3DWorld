#pragma once
class GameObject
{
private:
	D3DXMATRIXA16 m_wMatrix; 

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Scale;
	D3DXVECTOR3 m_Rotation;
	
	D3DXVECTOR3 m_Size;

	float m_RotX;
	float m_RotY;
	float m_RotZ;

private:
	GameObject* m_Parent;
	std::list<GameObject*> m_Children;
	std::string m_Name;

	bool m_Active;

public:
	GameObject();
	virtual ~GameObject();

	virtual void Update();
	virtual void Render();

	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);


public:

};

