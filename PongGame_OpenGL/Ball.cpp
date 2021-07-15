#include "Ball.h"

void Ball::Init() {
	SpriteRenderer::Init();
	mMoveVector = glm::vec3(-1, 0, 0);
	mTimeCount = 0.0f;
	mBallStart = true;
}
void Ball::Uninit() {
	SpriteRenderer::Uninit();
}
void Ball::Update() {

	SpriteRenderer::Update();
	Position += mMoveVector * 10.0f;

	if (Position.x <= -30.0f) {
		Position = glm::vec3((SCREEN_WIDTH - 30) / 2, (SCREEN_HEIGHT - 30) / 2, 0);
		SetMoveVector(glm::vec3(0, 0, 0));
		mBallStart = false;
		std::cout << "Player_2 Win " << std::endl;
		GetApp()->p2_score++;
	}
	else if (Position.x >= SCREEN_WIDTH + 30.0f) {
		Position = glm::vec3((SCREEN_WIDTH - 30) / 2, (SCREEN_HEIGHT - 30) / 2, 0);
		SetMoveVector(glm::vec3(0, 0, 0));
		mBallStart = false;
		std::cout << "Player_1 Win " << std::endl;
		GetApp()->p1_score++;
	}

	auto hitcheck_upwall = Hitcheck(glm::vec3(0,0,0), glm::vec3(SCREEN_WIDTH, 0, 0), Position, 15);
	if (hitcheck_upwall) {
		glm::vec3 moveDir = glm::normalize(mMoveVector);
		glm::vec3 normal_n = glm::normalize(glm::vec3(0, -0.5, 0));
		glm::vec3 r = glm::normalize(moveDir - 2.0f * glm::dot(glm::vec3(0, -0.5, 0), normal_n) * normal_n);
		SetMoveVector(r);
	}
	auto hitcheck_downwall = Hitcheck(glm::vec3(0, SCREEN_HEIGHT, 0), glm::vec3(SCREEN_WIDTH, SCREEN_HEIGHT, 0), Position, 15);
	if (hitcheck_downwall) {
		glm::vec3 moveDir = glm::normalize(mMoveVector);
		glm::vec3 normal_n = glm::normalize(glm::vec3(0, 0.5, 0));
		glm::vec3 r = glm::normalize(moveDir - 2.0f * glm::dot(glm::vec3(0, 0.5, 0), normal_n) * normal_n);
		SetMoveVector(r);
	}

	if (!mBallStart) {
		mTimeCount += 1.0f;
	}
	if (mTimeCount >= 180.0f) {
		SetMoveVector(glm::vec3(1, 0, 0));
		mBallStart = true;
		mTimeCount = 0.0f;
	}
}
void Ball::Draw() {
	SpriteRenderer::Draw();
}
void Ball::SetMoveVector(glm::vec3 vec) {
	mMoveVector = vec;
}