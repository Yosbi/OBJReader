#pragma once
#include <d3d12.h>
#include <directxmath.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

struct OBJVertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texture;
	DirectX::XMFLOAT3 normal;
};

struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};