#include "stdafx.h"
#include "Terrain.h"


VERTEX g_TerrainVertex[] = {
	{ D3DXVECTOR3(-25.f, 0.f, 25.f), D3DXVECTOR2(0,0) },
{ D3DXVECTOR3(25.f, 0.f, 25.f), D3DXVECTOR2(1,0) },
{ D3DXVECTOR3(25.f, 0.f, -25.f), D3DXVECTOR2(1,1) },

{ D3DXVECTOR3(-25.f, 0.f, 25.f), D3DXVECTOR2(0,0) },
{ D3DXVECTOR3(25.f, 0.f, -25.f), D3DXVECTOR2(1,1) },
{ D3DXVECTOR3(-25.f, 0.f, -25.f), D3DXVECTOR2(0,1) }
};

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
	m_pVB->Release();
	m_pIB->Release();
}

void Terrain::TextureInit(std::string fileName)
{
	if (FAILED(D3DXCreateTextureFromFile(D3DRenderer::GetInstance()->GetDevice(), fileName.c_str(), &m_Texture)))
	{
		printf("텍스쳐 생성 실패\n");
	}
}

void Terrain::Init()
{
	HANDLE hFile = CreateFile("./Resource/Height.bmp", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (0 == hFile)
		return;

	DWORD dwByte = 0;

	BITMAPFILEHEADER bitmapfileHeader;
	ReadFile(hFile, &bitmapfileHeader, sizeof(BITMAPFILEHEADER), &dwByte, nullptr);

	BITMAPINFOHEADER bitmapInfoHeader;
	ReadFile(hFile, &bitmapInfoHeader, sizeof(BITMAPINFOHEADER), &dwByte, nullptr);

	DWORD* dwPixel = new DWORD[bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight];
	ReadFile(hFile, dwPixel, sizeof(DWORD) * bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight, &dwByte, nullptr);

	TextureInit("./Resource/Tile.tga");

	VertexFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	dwTerrainX = 129;
	dwTerrainZ = 129;

	if (FAILED(D3DRenderer::GetInstance()->GetDevice()->CreateVertexBuffer(dwTerrainX * dwTerrainZ * sizeof(TEXVERTEX), 0, VertexFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
	{
		printf("xxxxx");
	}

	ZeroMemory(&m_Mtrl, sizeof(D3DMATERIAL9));
	m_Mtrl.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_Mtrl.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_Mtrl.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_Mtrl.Power = 3;

	TEXVERTEX* vertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&vertex, 0);

	for (int i = 0; i < dwTerrainZ; i++) //129 * 129 만큼의 정점을 만든다.
	{
		for (int j = 0; j < dwTerrainX; j++)
		{
			int index = j + i * dwTerrainX;
			vertex[index].vPos = D3DXVECTOR3(j, (dwPixel[index] & 0x000000ff) / 10.f, i); //불러온 비트맵의 컬러 중 b 의 값과 AND 연산해서 참인 값을 적절히 10으로 나눠서 Y값을 설정한다.
			vertex[index].vUV = D3DXVECTOR2((20.f * j) / dwTerrainX, (20.f * i) / dwTerrainZ); //0 ~ 128 의 배열을 0 ~ 20의 uv로 바꾸기 위해 Terrain의 X,Z로 나눠준다.
																								//20을 곱하는 이유는 배열이 129 까지 가면 129 / 129 로 1 이 되니까 20을 곱해준다.
			vertex[index].vNormal = D3DXVECTOR3(0, 1, 0);
		}
	}

	m_pVB->Unlock();

	if (FAILED(D3DRenderer::GetInstance()->GetDevice()->CreateIndexBuffer(sizeof(INDEX) * 128 * 128 * 2, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIB, nullptr)))
	{
		printf("");
	}
	
	INDEX* pindex = nullptr;

	int iTriIndex = 0;

	m_pIB->Lock(0, 0, (void**)&pindex, 0);

	for (int i = 0; i < dwTerrainZ - 1; i++) //인덱스 버퍼 , 
	{
		for (int j = 0; j < dwTerrainX - 1; j++) //-1 을 하는 이유는 사각형을 하나 만들 때는 쓰는 정점은 두개 만들때는 3개가 필요하기 때문에 밑의 indexArr 에서 + 1을 하면 dwTerrain에 -1을 안했으면
												//129로 넘어가기 때문이다.
		{
			int index = j + i * dwTerrainX; 

			int indexArr[] =
			{
				/*
				.
				.
				.
				0    1   0    1    0    1  ...
				3    2   3    2    3    2  ...
				*/
				index + dwTerrainX, //그리는 순서의 첫번째는 0번째니까 , 첫번째 줄에서 두번째줄로 갈려면 Terrain의 X만큼 더해준다.
				index + dwTerrainX + 1, //1은 0 에서 +1
				index + 1, //2 는 3에서 +1
				index
			};

			//시계방향으로 그린다.
			pindex[iTriIndex]._1 = indexArr[0];
			pindex[iTriIndex]._2 = indexArr[1];
			pindex[iTriIndex]._3 = indexArr[2];

			//루프를 돌면서 인덱스를 높이면서 삼각형 그리는 순서를 다 설정해준다.
			iTriIndex++;

			pindex[iTriIndex]._1 = indexArr[0];
			pindex[iTriIndex]._2 = indexArr[2];
			pindex[iTriIndex]._3 = indexArr[3];

			iTriIndex++;
		}
	}

	m_pIB->Unlock();


	CloseHandle(hFile);
}

void Terrain::Update()
{
	GameObject::Update();

	//printf("m_RotY : %f\n", m_RotY);

}

void Terrain::Render()
{
	GameObject::Render();

	D3DRenderer::GetInstance()->GetDevice()->SetMaterial(&m_Mtrl);
	D3DRenderer::GetInstance()->GetDevice()->SetIndices(m_pIB);
	D3DRenderer::GetInstance()->GetDevice()->SetFVF(VertexFVF);
	D3DRenderer::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(TEXVERTEX));

	D3DRenderer::GetInstance()->GetDevice()->SetTexture(0, m_Texture);

	D3DRenderer::GetInstance()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, dwTerrainX * dwTerrainZ, 0, (dwTerrainX - 1) * (dwTerrainZ - 1) * 2);
}