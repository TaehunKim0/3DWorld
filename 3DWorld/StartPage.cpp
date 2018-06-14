#include"stdafx.h"


INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{

#if _DEBUG
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "wt", stdout);

#endif
	D3DApp* app = D3DApp::GetInstance();

	D3DXMATRIX m1;
	MatrixIdentity(&m1);
	MatrixRotationYawPitchRoll(&m1, D3DXToRadian(30), D3DXToRadian(30), D3DXToRadian(30));

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%7.1f", m1(i, j));
		}
		printf("\n");
	}

	srand(time(NULL));

	if (app->Initialize(1280, 720, 0))
		app->RunGame();

	

	app->Release();

#if _DEBUG
	FreeConsole();
#endif
	return S_OK;
}