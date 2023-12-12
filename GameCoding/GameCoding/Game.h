﻿#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private: 
	void RenderBegin(); 
	void RenderEnd(); 

private:
	void CreateDeviceAndSwapChain(); 
	void CreateRenderTargetView(); 
	void SetViewport(); 

private: 
	void CreateGeometry(); 
	void CreateInputLayout();

	void CreateVS(); 
	void CreatePS(); 

	void CreateSRV(); 

	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob); 

private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	// Device & SwapChain
	ComPtr<ID3D11Device> _device = nullptr; 
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr; 
	ComPtr<IDXGISwapChain> _swapChain = nullptr; 

	// RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView; // 후면 버퍼를 묘사하는 존재

	// Misc
	D3D11_VIEWPORT _viewport = { 0 }; // 화면의 크기를 묘사
	float _clearColor[4] = { 0.f, 0.f, 0.f, 0.f };
	
private: 
	// Geometry
	vector<Vertex> _vertices; 
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr; 
	vector<uint32> _indices; // uint16 중 선택사항인데 일단은 4바이트로 가본다.인덱스 목록 CPU에 들고 있음. 
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr; 
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr; 
	ComPtr<ID3DBlob> _vsBlob = nullptr; 

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr; 
	ComPtr<ID3DBlob> _psBlob = nullptr; 

	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr; 
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2 = nullptr; 

	// [CPU <-> RAM] [GPU <-> VRAM]
};