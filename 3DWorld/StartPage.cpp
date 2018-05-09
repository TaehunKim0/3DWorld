#include"stdafx.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{

#if _DEBUG
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "wt", stdout);
#endif
	//App -> Init

	//App -> Release
#if _DEBUG
	FreeConsole();
#endif
	return S_OK;
}