#pragma once
#include "Resource.h"

class Light :public Resource
{

private:

	GLuint VAO;
	GLuint VBO;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetLight();
};

