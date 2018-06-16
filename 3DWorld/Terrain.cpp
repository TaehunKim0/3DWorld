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
		printf("�ؽ��� ���� ����\n");
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

	for (int i = 0; i < dwTerrainZ; i++) //129 * 129 ��ŭ�� ������ �����.
	{
		for (int j = 0; j < dwTerrainX; j++)
		{
			int index = j + i * dwTerrainX;
			vertex[index].vPos = D3DXVECTOR3(j, (dwPixel[index] & 0x000000ff) / 10.f, i); //�ҷ��� ��Ʈ���� �÷� �� b �� ���� AND �����ؼ� ���� ���� ������ 10���� ������ Y���� �����Ѵ�.
			vertex[index].vUV = D3DXVECTOR2((20.f * j) / dwTerrainX, (20.f * i) / dwTerrainZ); //0 ~ 128 �� �迭�� 0 ~ 20�� uv�� �ٲٱ� ���� Terrain�� X,Z�� �����ش�.
																								//20�� ���ϴ� ������ �迭�� 129 ���� ���� 129 / 129 �� 1 �� �Ǵϱ� 20�� �����ش�.
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

	for (int i = 0; i < dwTerrainZ - 1; i++) //�ε��� ���� , 
	{
		for (int j = 0; j < dwTerrainX - 1; j++) //-1 �� �ϴ� ������ �簢���� �ϳ� ���� ���� ���� ������ �ΰ� ���鶧�� 3���� �ʿ��ϱ� ������ ���� indexArr ���� + 1�� �ϸ� dwTerrain�� -1�� ��������
												//129�� �Ѿ�� �����̴�.
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
				index + dwTerrainX, //�׸��� ������ ù��°�� 0��°�ϱ� , ù��° �ٿ��� �ι�°�ٷ� ������ Terrain�� X��ŭ �����ش�.
				index + dwTerrainX + 1, //1�� 0 ���� +1
				index + 1, //2 �� 3���� +1
				index
			};

			//�ð�������� �׸���.
			pindex[iTriIndex]._1 = indexArr[0];
			pindex[iTriIndex]._2 = indexArr[1];
			pindex[iTriIndex]._3 = indexArr[2];

			//������ ���鼭 �ε����� ���̸鼭 �ﰢ�� �׸��� ������ �� �������ش�.
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