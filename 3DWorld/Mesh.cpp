#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
	//m_Mesh->Release();
}

Mesh * Mesh::Create(std::string fileName, std::string Name)
{
	auto mesh = new(std::nothrow) Mesh();
	if (mesh && mesh->Init(fileName , Name))
	{
		return mesh;
	}

	SafeDelete(mesh);
	return nullptr;
}

bool Mesh::Init(std::string fileName , std::string Name)
{
	LPD3DXBUFFER mtrBuffer;
	std::string bf;

	bf = fileName + Name;

	if (FAILED(D3DXLoadMeshFromX(bf.c_str(), D3DXMESH_SYSTEMMEM,
		D3DRenderer::GetInstance()->GetDevice(), NULL, &mtrBuffer, NULL, &m_NumsMaterial, &m_Mesh)))
	{
		MessageBox(NULL, "X File None", "3DWorld.exe", MB_OK);
		return false;
	}

	//���������� �ؽ��� ���� ���� �̾Ƴ���.
	D3DXMATERIAL* d3dMaterials = (D3DXMATERIAL*)mtrBuffer->GetBufferPointer();

	m_MeshMaterials = new D3DMATERIAL9[m_NumsMaterial]; //���� ���� ��ŭ ��������ü �迭 ����
	m_MeshTextures = new LPDIRECT3DTEXTURE9[m_NumsMaterial]; //���� ���� ��ŭ �ؽ��� �迭 ����

	D3DVERTEXELEMENT9 dcl[65];

	ZeroMemory(dcl, sizeof(D3DVERTEXELEMENT9) * 65);

	m_Mesh->GetDeclaration(dcl);

	for (DWORD i = 0; i < m_NumsMaterial; i++)
	{
		//���������� ����
		m_MeshMaterials[i] = d3dMaterials[i].MatD3D;

		//�ֺ� ���������� Diffuse ������
		m_MeshMaterials[i].Ambient = D3DXCOLOR(1.f,1.f,1.f,1.f);

		m_MeshTextures[i] = NULL;

		bf = fileName;

		if (d3dMaterials[i].pTextureFilename != NULL && lstrlen(d3dMaterials[i].pTextureFilename) > 0)
		{
			bf += d3dMaterials[i].pTextureFilename;

			//�ؽ��ĸ� ���Ͽ��� �ε��Ѵ�.
			if (FAILED(D3DXCreateTextureFromFile(D3DRenderer::GetInstance()->GetDevice(), bf.c_str(), &m_MeshTextures[i])))
			{
				MessageBox(NULL, "Texture is None", "3DWorld.exe", MB_OK);
				return false;
			}

		/*	if (FAILED(D3DXCreateTextureFromFileEx(D3DRenderer::GetInstance()->GetDevice(), (d3dMaterials[i].pTextureFilename),
				D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
				1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
				D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL,
				&m_MeshTextures[i])))
			{
				MessageBox(NULL, "Texture is None", "3DWorld.exe", MB_OK);
				return false;
			}*/
		}
	}

	mtrBuffer->Release();

	return true;
}

void Mesh::Update()
{
	GameObject::Update();
}

void Mesh::Render()
{
	GameObject::Render();
	
	D3DRenderer::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &m_wMatrix); // ���� ��Ʈ���� ����
																					//Tiger ����
	for (DWORD i = 0; i < m_NumsMaterial; i++)
	{
		D3DRenderer::GetInstance()->GetDevice()->SetMaterial(&m_MeshMaterials[i]);
		D3DRenderer::GetInstance()->GetDevice()->SetTexture(0, m_MeshTextures[i]);
		m_Mesh->DrawSubset(i);
	}

}