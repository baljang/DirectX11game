#pragma once
#include "Component.h"

class MeshRenderer :  public Component
{
	using Super = Component; 

public: 
	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~MeshRenderer(); 

	virtual void Update() override;

	void Render(shared_ptr<Pipeline> pipeline); 

private: 
	ComPtr<ID3D11Device> _device;

	// Mesh
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	// shared_ptr<Geometry<VertexColorData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;

	// Material
	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<PixelShader> _pixelShader;
	shared_ptr<Texture> _texture1;
	shared_ptr<SamplerState> _samplerState;
	shared_ptr<BlendState> _blendState;

private:
	// Camera
	CameraData _cameraData;
	shared_ptr<ConstantBuffer<CameraData>> _cameraBuffer;

	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _transformBuffer;


};
