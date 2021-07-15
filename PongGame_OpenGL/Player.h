#pragma once

#include "SpriteRenderer.h"
#include "Ball.h"

class Player : public SpriteRenderer
{

private:

	Ball* mptrBall;
	float mCollisionTimer;
	bool mCollisionActive;

public:

	int index;

	void Init();
	void Uninit();
	void UpdateCollision();
	void Update();
	void Draw();
	
};

