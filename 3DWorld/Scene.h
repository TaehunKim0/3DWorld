#pragma once
class Scene : public GameObject
{
protected:
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;

	D3DXVECTOR3 EyePt;
	D3DXVECTOR3 LookAtPt;
	D3DXVECTOR3 UpVec;

public:
	Scene();
	virtual ~Scene();

	virtual void SetUpMatrix();

};

