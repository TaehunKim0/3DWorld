#pragma once

struct tagVertex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR2 vUV;
}typedef VERTEX;





class Terrain : public GameObject
{
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;


public:
	Terrain();
	~Terrain();


	void Init();


	void Update();
	void Render();


};

