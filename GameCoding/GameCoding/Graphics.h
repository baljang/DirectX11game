﻿#pragma once
class Graphics
{
public: 
	Graphics(HWND hwnd); 
	~Graphics(); 

	void RenderBegin(); 
	void RenderEnd(); 

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }

private: 
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

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
	float _clearColor[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
};

