#pragma once

#include "SpriteRenderer.h"

class Ball : public SpriteRenderer
{
private:

	glm::vec3 mMoveVector;
	bool mBallStart;
	float mTimeCount;

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetMoveVector(glm::vec3 vec);
	glm::vec3 GetMoveVector() { return mMoveVector; };
};

