#pragma once
#include "OBJVertex.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

	std::vector<OBJVertex> LoadOBJ(std::wstring sFileName, bool bCreateVertexPosColorRandom);

	std::vector<Vertex> getVertexPosColor();
	std::vector<WORD> getIndex();

private:

	float getRandom();

	std::vector<std::string> GetTokens(std::string sLine, char c);

	std::vector<WORD> index;
	std::vector<Vertex> vertexPosColor;


	std::vector<DirectX::XMFLOAT3> vertices;
	std::vector<DirectX::XMFLOAT2> textures;
	std::vector<DirectX::XMFLOAT3> normals;
};

