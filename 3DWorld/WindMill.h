#pragma once


class WindMill : public GameObject
{
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;
	D3DMATERIAL9 m_Mtrl;

	LPDIRECT3DVERTEXBUFFER9 m_pVBw;
	LPDIRECT3DINDEXBUFFER9 m_pIBw;

	D3DXMATRIX m_wingTransform;
	D3DXMATRIX m_wingWorldTransform;
	float WingAngle;

	bool bWingShoot;


public:
	void Init();

	WindMill();
	~WindMill();

public:
	void Update();
	void Render();

};

