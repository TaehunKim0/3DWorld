#pragma once
class Mesh : public GameObject
{
public:
	D3DMATERIAL9* m_MeshMaterials;
	LPDIRECT3DTEXTURE9* m_MeshTextures;
	LPD3DXMESH m_Mesh;

	DWORD m_NumsMaterial;

public:
	Mesh();
	virtual ~Mesh();

	static Mesh* Create(std::string fileName, std::string Name);
	bool Init(std::string fileName, std::string Name);

	virtual void Update();
	virtual void Render();
};