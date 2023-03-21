#ifndef D3D_APP_H
#define D3D_APP_H

#pragma once

#include "D3DUtil.h"
#include "OBJLoader.h"

using namespace DirectX;

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	~D3DApp();

	static D3DApp* GetD3DApp();

	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool Initialize();
	void OnResize();
	
	bool InitMainWindow();
	bool InitDirect3D();
	void CreateCommandObjects();
	void CreateSwapChain();
	void CreateRtvAndDsvDescriptorHeaps();
	void LoadTriangles();
	int Run();
	void Update();
	void Draw();
	void DrawTriangles();

	void FlushCommandQueue();

	void UpdateBufferResource(
		ComPtr<ID3D12GraphicsCommandList2> commandList,
		ID3D12Resource** pDestinationResource,
		ID3D12Resource** pIntermediateResource,
		size_t numElements, size_t elementSize, const void* bufferData);

	D3D12_CPU_DESCRIPTOR_HANDLE getDepthStencilView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE getCurrentBackBufferView() const;
	ID3D12Resource* getCurrentBackBuffer() const;

private:
	static D3DApp* sm_this;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	Microsoft::WRL::ComPtr<IDXGIFactory4> m_dxgiFactory;
	Microsoft::WRL::ComPtr<ID3D12Device> m_d3dDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;

	// Fence stuff (cpu/gpu sync)
	Microsoft::WRL::ComPtr<ID3D12Fence> m_Fence;
	UINT64 m_nCurrentFence = 0;

	// Buffers formats
	DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM; // Backbuffer format
	DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT; // DeepStencil format

	// Buffer descriptors sizes
	UINT m_RtvDescriptorSize = 0;		// Render target 
	UINT m_DsvDescriptorSize = 0;		// Deep Stencil 
	UINT m_CbvSrvUavDescriptorSize = 0;	// Constant buffer

	// Buffer Descriptor heaps
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_DsvHeap;

	// Swap chain stuff and actual buffers refs
	static const int sm_nSwapChainBufferCount = 2;
	int m_nCurrBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_SwapChainBuffer[sm_nSwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> m_DepthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_IndexBuffer;

	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW m_IndexBufferView;

	// Multisampling 
	bool      m_b4xMsaaState = false;    // 4X MSAA enabled
	UINT      m_n4xMsaaQuality = 0;      // quality level of 4X MSAA

	// Command objects
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_CmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> m_CommandList;

	// Viewport and sissor
	D3D12_VIEWPORT m_ScreenViewport;
	D3D12_RECT m_ScissorRect;

	// Shader stuff
	ComPtr<ID3D12RootSignature> m_rootSignature;
	ComPtr<ID3D12PipelineState> m_pipelineState;

	int m_nClientWidth = 1280;
	int m_nClientHeight = 720;

	float m_FoV;

	DirectX::XMMATRIX m_WorldMatrix;
	DirectX::XMMATRIX m_ViewMatrix;
	DirectX::XMMATRIX m_ProjectionMatrix;

	OBJLoader m_objLoader;
};
#endif

