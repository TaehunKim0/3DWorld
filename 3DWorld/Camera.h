#pragma once

class Camera : public GameObject , public Singleton<Camera>
{
public:
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;

	D3DXVECTOR3 EyePt;
	D3DXVECTOR3 LookAtPt;
	D3DXVECTOR3 UpVec;
	D3DXVECTOR3 RightVec;


	GameObject* m_Target;

	bool CameraFreeView;

	float fRotX;
	float fRotY;

public:
	Camera();
	virtual ~Camera();

	void Update();

public:
	void SetTarget(GameObject* target);
	void SetCameraThirdPerson(GameObject* target);
	void SetCameraFreeView();

public:
	void ForwardOrBackword(float fDelta);
	void LeftOrRight(float fDelta);
	void UpOrDown(float fDelta);
};

