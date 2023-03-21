#include "OBJLoader.h"

OBJLoader::OBJLoader() {
	srand(time(0));
}


OBJLoader::~OBJLoader() {}

float OBJLoader::getRandom() {
	
	return (float) (rand() / (float)RAND_MAX);
}

std::vector<OBJVertex> OBJLoader::LoadOBJ(std::wstring sFileName, bool bCreateVertexPosColorRandom)
{
	std::ifstream inFile(sFileName);

	std::vector<OBJVertex> objVerteces;


	if (inFile.is_open())
	{
		std::string line;
		while (std::getline(inFile, line))
		{
			std::vector<std::string> tokens = GetTokens(line, ' ');
			if (!tokens.empty())
			{
				// Loading vertices
				if (tokens[0] == "v")
				{
					vertices.push_back(DirectX::XMFLOAT3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])));

					if (bCreateVertexPosColorRandom)
						vertexPosColor.push_back(Vertex{ DirectX::XMFLOAT3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]))
							, DirectX::XMFLOAT4(getRandom(), getRandom() ,getRandom(), 1.0f)});
				}
				else if (tokens[0] == "vt")
				{
					textures.push_back(DirectX::XMFLOAT2(std::stof(tokens[1]), std::stof(tokens[2])));
				}
				else if (tokens[0] == "vn")
				{
					normals.push_back(DirectX::XMFLOAT3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])));
				}
				else if (tokens[0] == "f")
				{ 
					for (int i = 1; i < 4; i++)
					{
						std::vector<std::string> faceV = GetTokens(tokens[i], '/');

						OBJVertex objVertex;
						objVertex.position = vertices[std::stoi(faceV[0]) - 1];
						objVertex.texture = textures[std::stoi(faceV[1]) - 1];
						objVertex.normal = normals[std::stoi(faceV[2]) - 1];

						if (bCreateVertexPosColorRandom)
							index.push_back(std::stoi(faceV[0]) - 1);
						
						objVerteces.push_back(objVertex);
					}
				}
			}
		}
	}

	if (bCreateVertexPosColorRandom)
		std::reverse(index.begin(), index.end());



	return objVerteces;
}

std::vector<Vertex> OBJLoader::getVertexPosColor()
{
	return vertexPosColor;
}

std::vector<WORD> OBJLoader::getIndex()
{
	return index;
}


std::vector<std::string> OBJLoader::GetTokens(std::string sLine, char c)
{
    // Vector of string to save tokens
    std::vector <std::string> tokens;

    // stringstream class check1
	std::stringstream check1(sLine.c_str());

    std::string intermediate;
	
	// Tokenizing
    while (getline(check1, intermediate, c))
    {
        tokens.push_back(intermediate);
    }

	return tokens;

}

