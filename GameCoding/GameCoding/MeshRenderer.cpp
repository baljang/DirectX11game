#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext) 
	: Super(ComponentType::MeshRenderer), _device(device)
{
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);
	// _geometry = make_shared<Geometry<VertexColorData>>();
	//GeometryHelper::CreateRectangle(_geometry, Color{1.0f, 0.f, 0.f, 1.0f});

	_vertexBuffer = make_shared<VertexBuffer>(device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>(device);
	_indexBuffer->Create(_geometry->GetIndices());

	_vertexShader = make_shared<VertexShader>(device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	_inputLayout = make_shared<InputLayout>(device);
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());
	//_inputLayout->Create(VertexColorData::descs, _vertexShader->GetBlob());

	_pixelShader = make_shared<PixelShader>(device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	_rasterizerState = make_shared<RasterizerState>(device);
	_rasterizerState->Create();

	_blendState = make_shared<BlendState>(device);
	_blendState->Create();

	_cameraBuffer = make_shared<ConstantBuffer<CameraData>>(device, deviceContext);
	_cameraBuffer->Create();

	_transformBuffer = make_shared<ConstantBuffer<TransformData>>(device, deviceContext);
	_transformBuffer->Create();


	_texture1 = make_shared<Texture>(device);
	_texture1->Create(L"chiikawa.png");

	_samplerState = make_shared<SamplerState>(device);
	_samplerState->Create();
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{
	_cameraData.matView = Camera::S_MatView;
	//_cameraData.matView = Matrix::Identity;
	_cameraData.matProjection = Camera::S_MatProjection;
	//_cameraData.matProjection = Matrix::Identity;
	_cameraBuffer->CopyData(_cameraData);

	_transformData.matWorld = GetTransform()->GetWorldMatrix();
	_transformBuffer->CopyData(_transformData);
}

void MeshRenderer::Render(shared_ptr<Pipeline> pipeline)
{
	// IA - VS - RS - PS - OM
	PipelineInfo info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;
	pipeline->UpdatePipeline(info);

	pipeline->SetVertexBuffer(_vertexBuffer);
	pipeline->SetIndexBuffer(_indexBuffer);

	pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraBuffer);
	pipeline->SetConstantBuffer(1, SS_VertexShader, _transformBuffer);

	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);

}
