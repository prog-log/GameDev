#pragma once
class Mesh;

class Model
{
public:
	Model();
	~Model();

	bool Setup(Renderer& renderer, const char* filePath);
	void Terminate();

	void Draw(Renderer& renderer);

private:
	void setupTransform(Renderer& renderer);

private:
	Mesh*	meshes_ = nullptr;
	u_int	meshNum_ = 0;
};
