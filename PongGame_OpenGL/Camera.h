#pragma once

#include "Resource.h"


class Camera : public Resource
{
private:
	
	glm::vec3 front;
	glm::vec3 up;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 projection2d;
	glm::mat4 model;

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetCamera(int type);

};

