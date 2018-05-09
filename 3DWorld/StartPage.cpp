#include"stdafx.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{

#if _DEBUG
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "wt", stdout);

#endif
	D3DApp* app = D3DApp::GetInstance();

	if (app->Initialize(1280, 720, 0))
		app->RunGame();

	app->Release();

#if _DEBUG
	FreeConsole();
#endif
	return S_OK;
}