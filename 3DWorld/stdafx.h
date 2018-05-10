#pragma once

#define SafeDelete(x) if(x) {delete x; x = nullptr;}
#define SafeRelease(x) if(x) {x->Release(); x = nullptr;}


#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<mmsystem.h>
#include<vector>
#include<list>

#include"Singleton.h"
#include"D3DApp.h"
#include"D3DRenderer.h"