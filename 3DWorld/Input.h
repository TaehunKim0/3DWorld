#pragma once

enum class KeyState
{
	None = 0,
	Down,
	Pressed,
	Up
};

enum MouseButton
{
	Left = VK_LBUTTON,
	Right = VK_RBUTTON
};

class Input : public Singleton<Input>
{
private:
	bool m_PrevKeyState[256];
	bool m_NowKeyState[256];

	bool m_RButtonDown;

	bool prevState;
	bool nowState;

	D3DXVECTOR2 m_vMousePosition;
	D3DXVECTOR2 m_vDeltaMove;

public:
	Input();
	~Input();

	void ButtonDown(bool down);
	void Update();

	KeyState GetKeyState(int key);
	KeyState GetMouseState(int button);

	inline D3DXVECTOR2 GetMousePosition()
	{
		return m_vMousePosition;
	}

	inline D3DXVECTOR2 GetDeltaMove()
	{
		return m_vDeltaMove;
	}

	inline bool GetButtonDown()
	{
		return m_RButtonDown;
	}


	void UpdateKeyState();
	void UpdateMouseState();
};