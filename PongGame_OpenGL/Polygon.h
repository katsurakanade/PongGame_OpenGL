#pragma once

#include "Texture.h"
#include "Resource.h"
#include "Camera.h"

enum class Type {
	Default,
	Light,
};

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

class Polygon : public Resource
{

private:

	GLuint* vertexbuffer;
	GLuint* VAO;
	glm::mat4 trans;
	glm::mat4 model;
	Texture* texture;

public:

	bool is_light = false;

	Material material;

	void Init();
	void Uninit();
	void Update();
	void Draw(Type type,Polygon light);
	void Draw() {};

	void SetTexture(Texture* data);
};

