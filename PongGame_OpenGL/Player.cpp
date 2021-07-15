
#include "Player.h"

void Player::Init() {
	SpriteRenderer::Init();
	mptrBall = GetApp()->GetGameObject<Ball>(_2D);
	mCollisionActive = true;
	mCollisionTimer = 0.0f;
}
void Player::Uninit() {
	SpriteRenderer::Uninit();
}
void Player::UpdateCollision() {
	if (mCollisionActive) {
		auto hitcheck = Hitcheck(Position + glm::vec3(0, 55, 0), Position + glm::vec3(0, -55, 0), mptrBall->Position, 15);
		if (hitcheck) {
			if (index == 0) {
				float y_offset = (mptrBall->Position.y - Position.y);
				glm::vec3 moveDir = glm::normalize(mptrBall->GetMoveVector());
				glm::vec3 normal_n = glm::normalize(glm::vec3(-1, -y_offset / 10, 0));
				glm::vec3 r = glm::normalize(moveDir - 2.0f * glm::dot(glm::vec3(-1, -y_offset / 10, 0), normal_n) * normal_n);
				mptrBall->SetMoveVector(r);
				mCollisionActive = false;
			}
			else if (index == 1) {
				float y_offset = (mptrBall->Position.y - Position.y);
				std::cout << y_offset << std::endl;
				glm::vec3 moveDir = glm::normalize(mptrBall->GetMoveVector());
				glm::vec3 normal_n = glm::normalize(glm::vec3(1, -y_offset / 10, 0));
				glm::vec3 r = glm::normalize(moveDir - 2.0f * glm::dot(glm::vec3(1, -y_offset / 10, 0), normal_n) * normal_n);
				mptrBall->SetMoveVector(r);
				mCollisionActive = false;
			}
		}
	}

	if (!mCollisionActive) {
		mCollisionTimer += 1.0f;
	}
	if (mCollisionTimer > 60.0f) {
		mCollisionTimer = 0.0f;
		mCollisionActive = true;
	}
}
void Player::Update() {

	if (index == 0) {

		if (Position.y < SCREEN_HEIGHT - 100) {
			if (glfwGetKey(GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
				Position.y += 10.0f;
			}
		}

		if (Position.y > 0) {
			if (glfwGetKey(GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
				Position.y -= 10.0f;
			}
		}
	}
	else if (index == 1) {
		
		float offset_y = Position.y - mptrBall->Position.y;
		if (abs(offset_y) > 30) {
			if (offset_y > 0) {
				Position.y -= 25.0f;
			}
			else if (offset_y < 0) {
				Position.y += 25.0f;
			}
		}

		/*if (Position.y < SCREEN_HEIGHT - 100) {
			if (glfwGetKey(GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
				Position.y += 10.0f;
			}
		}

		if (Position.y > 0) {
			if (glfwGetKey(GetWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
				Position.y -= 10.0f;
			}
		}*/
	}

	SpriteRenderer::Update();
}
void Player::Draw() {
	SpriteRenderer::Draw();
}
