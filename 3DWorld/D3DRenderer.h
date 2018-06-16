#pragma once
class D3DRenderer : public Singleton<D3DRenderer>
{
private:
	LPDIRECT3D9 m_D3D;
	LPDIRECT3DDEVICE9 m_Device;
	D3DLIGHT9 Light;
	bool m_bWireFrame;

	float m_fX;

public:
	D3DRenderer();
	~D3DRenderer();

	void Release();

	bool Initialize(int width, int height, HWND hWnd, bool windowed);

	void RenderBegin();
	void RenderEnd();

	LPDIRECT3DDEVICE9 GetDevice() {
		return m_Device;
	}
	
};