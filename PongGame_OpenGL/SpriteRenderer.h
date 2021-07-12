#pragma once

#include "Resource.h"
#include "Texture.h"

class SpriteRenderer : public Resource
{

protected:

	GLuint* vertexbuffer;
	GLuint* VAO;
	glm::vec2 Size;
	Texture* texture;

public:

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	void SetTexture(Texture* data);

	void SetSize(glm::vec2 value) { this->Size = value; };
};

