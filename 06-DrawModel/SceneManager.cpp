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

	const char* MODEL_PATH = "C:/Users/Keita/projects/GameDev/Assets/box.fbx";
	sampleModel_.Setup(renderer, MODEL_PATH);
}

void SceneManager::Terminate()
{
	sampleModel_.Terminate();
}

void SceneManager::Update()
{
	camera_.Update();
}

void SceneManager::Draw()
{
	auto viewMatrix = camera_.GetViewMatrix();
	pRenderer_->SetupViewTransform(viewMatrix);

	sampleModel_.Draw(*pRenderer_);
}

