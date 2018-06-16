#pragma once



class Terrain : public GameObject
{
private:
	LPDIRECT3DTEXTURE9 m_Texture;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;
	D3DMATERIAL9 m_Mtrl;

	DWORD dwTerrainX;
	DWORD dwTerrainZ;
public:
	Terrain();
	~Terrain();


	void TextureInit(std::string fileName);
	void Init();


	void Update();
	void Render();


};

