#pragma once
class ResourceMgr : public Singleton<ResourceMgr>
{
public:
	ResourceMgr();
	~ResourceMgr();

public:
	std::map<std::string, LPD3DXMESH> m_MeshMap;

	Mesh* CreateMeshFromFile(std::string fileName, std::string Name);

};

