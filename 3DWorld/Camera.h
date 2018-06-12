#pragma once
class Camera : public GameObject
{
public:
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;

	D3DXVECTOR3 EyePt;
	D3DXVECTOR3 LookAtPt;
	D3DXVECTOR3 UpVec;

	GameObject* m_Target;

	float m_fRotX;
	float m_fRotY;

public:
	Camera();
	virtual ~Camera();

	void Update();

	void SetTarget(GameObject* ptarget);

	void ForwardOrBackword(float fDelta);
	void LeftOrRight(float fDelta);
	void UpOrDown(float fDelta);
};

