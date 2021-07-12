#include "main.h"
#include "Shader.h"
#include "Cube.h"
#include "Camera.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Player.h"
#include "Ball.h"
#include "Light.h"
#include "Resource.h"
#include "Application.h"

Texture* boxtex;
Texture* title_logotex;

bool Application::Init() {

	Shader::Init(ShaderGroup::Default);
	Shader::Init(ShaderGroup::Light);
	Shader::Init(ShaderGroup::Sprite);

	mGameActive = false;

	boxtex = new Texture("asset/cpu.jpg",JPG);
	title_logotex = new Texture("asset/title_logo.png", PNG);

	auto lampcube = AddGameObject<Cube>(_Light);
	lampcube->Name = "LampCube";
	lampcube->Position = glm::vec3(0.0f, 0.0f, 0.0f);
	lampcube->Scale = glm::vec3(0.0f, 0.0f, 0.0f);
	lampcube->is_light = true;

	auto title_logo = AddGameObject<SpriteRenderer>(_2D);
	title_logo->Name = "Title_logo";
	title_logo->SetSize(glm::vec2(700,300));
	title_logo->Position = glm::vec3((SCREEN_WIDTH - 700) / 2, ((SCREEN_HEIGHT - 300) / 2) - 300, 0);
	title_logo->SetTexture(title_logotex);

	auto ball = AddGameObject<Ball>(_2D);
	ball->SetSize(glm::vec2(30, 30));
	ball->Position = glm::vec3((SCREEN_WIDTH - 30) / 2, (SCREEN_HEIGHT - 30) / 2, 0);
	ball->SetTexture(boxtex);

	auto player_1 = AddGameObject<Player>(_2D);
	player_1->SetTexture(boxtex);
	player_1->SetSize(glm::vec2(10, 100));
	player_1->Position = glm::vec3(20, (SCREEN_HEIGHT - 100) / 2, 0);
	player_1->color = glm::vec3(1, 1, 1);
	player_1->index = 0;

	auto player_2 = AddGameObject<Player>(_2D);
	player_2->SetTexture(boxtex);
	player_2->SetSize(glm::vec2(10, 100));
	player_2->Position = glm::vec3(SCREEN_WIDTH - 20, (SCREEN_HEIGHT - 100) / 2, 0);
	player_2->color = glm::vec3(1, 1, 1);
	player_2->index = 1;

	cm = AddGameObject<Camera>(_Camera);
	cm->Position = lampcube->Position + glm::vec3(0, 1.5, 5);
 
	return true;
}

void Application::Uninit() {

	Shader::Uninit();

	for (int i = 0; i < 4; i++) {
		for (Resource* g : mGameObject[i]) {
			g->Uninit();
			delete g;
			g = nullptr;
		}
		mGameObject[i].reverse();
	}

	delete boxtex;
	delete title_logotex;
	boxtex = nullptr;
	title_logotex = nullptr;
}

void Application::Update() {
	
	cm->Update();

	if (mGameActive) {

		for (int i = 1; i < 4; i++) {
			for (Resource* g : mGameObject[i])
			{
				g->UpdateCollision();
			}
		}

		for (int i = 1; i < 4; i++) {
			for (Resource* g : mGameObject[i])
			{
				g->Update();
			}
		}

		for (int i = 0; i < 4; i++) {
			mGameObject[i].remove_if([](Resource* obj) {return obj->Remove(); });
		}
	}

	if (!mGameActive && glfwGetKey(GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		mGameActive = true;
		auto obj = GetGameObjectWithName<SpriteRenderer>(_2D, "Title_logo");
		obj->Destroy();
	}

	{
		ImGui::Begin("Main");
		ImGui::Text("Camera Postion (%f,%f,%f)", cm->Position.x, cm->Position.y, cm->Position.z);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}

void Application::Render() {

	for (int i = 0; i < 4; i++) {
		cm->SetCamera(i);
		for (Resource* g : mGameObject[i])
		{
			if (g->mActive)
				g->Draw();
		}
	}

	
}

