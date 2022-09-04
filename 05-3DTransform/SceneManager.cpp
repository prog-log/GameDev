#include "SceneManager.h"
#include "Renderer.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize(Renderer& renderer)
{
	pRenderer_ = &renderer;

	sampleTriangle_.CreateVertexBuffer(renderer);
}

void SceneManager::Terminate()
{
	sampleTriangle_.DestroyVertexBuffer();
}

void SceneManager::Update()
{
	camera_.Update();
}

void SceneManager::Draw()
{
	auto viewMatrix = camera_.GetViewMatrix();
	pRenderer_->SetupViewTransform(viewMatrix);

	sampleTriangle_.Draw(*pRenderer_);
}

