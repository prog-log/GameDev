#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void Model::LoadMesh(const char* filePath)
{
	Assimp::Importer importer;
	UINT flag = 0;
	auto pScene = importer.ReadFile(filePath, flag);

	if (pScene == nullptr) return;
}

