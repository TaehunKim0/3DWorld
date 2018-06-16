#pragma once
struct tagVertex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNormal;
	D3DXCOLOR Diffuse;
}typedef VERTEX;

struct tagTexVertex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNormal;
	D3DXVECTOR2 vUV;
}typedef TEXVERTEX;

struct tagIndex
{
	DWORD _1, _2, _3;


}typedef INDEX;




class GameObject
{
public:
	D3DXMATRIXA16 m_wMatrix; 
	DWORD VertexFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

	D3DXMATRIXA16 matS; //스케일 매트릭스
	D3DXMATRIXA16 matRotY; //회전 매트릭스
	D3DXMATRIXA16 matRotX;
	D3DXMATRIXA16 matRotZ;
	D3DXMATRIXA16 matT; //이동 매트릭스

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Scale;
	D3DXVECTOR3 m_Rotation;
	
	float m_fRadius;

	D3DXVECTOR3 m_Size;

	float m_RotX;
	float m_RotY;
	float m_RotZ;

	bool m_Active;
private:
	GameObject* m_Parent;
	std::list<GameObject*> m_Children;
	std::string m_Name;


	bool m_UseParentMatrix;

public:
	GameObject();
	virtual ~GameObject();

	void SetMatrix();

	virtual void Update();
	virtual void Render();

	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);

	inline void SetScale(float x, float y, float z)
	{
		m_Scale.x = x;
		m_Scale.y = y;
		m_Scale.z = z;
	}

public:
	inline void Translate(float x, float y, float z)
	{
		m_Position.x += x;
		m_Position.y += y;
		m_Position.z += z;
	}

	inline void SetPosition(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}

};

