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

	LPDIRECT3DTEXTURE9 m_Texture;
	D3DXVECTOR3 vWingPosition;
	bool UsePm;

	D3DXMATRIX mTemp;
	D3DXVECTOR3 vDirTemp;


public:
	void Init();

	WindMill();
	~WindMill();

public:
	void Update();
	void Render();

};

