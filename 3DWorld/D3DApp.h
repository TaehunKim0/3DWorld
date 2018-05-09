#pragma once

class D3DApp : public Singleton<D3DApp>
{
private:
	HWND m_hWnd;

	UINT m_WindowWidth;
	UINT m_WindowHeight;
	bool m_Windowed;

public:
	D3DApp();
	~D3DApp();

	HWND GetHWND() {
		return m_hWnd;
	}

	bool Initialize(UINT width, UINT height, bool windowed);
	bool _CreateWindow();

	void Release();

public:
	static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l);

};

