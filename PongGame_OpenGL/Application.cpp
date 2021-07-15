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

	score_tex.push_back(new Texture("asset/0.png", PNG));
	score_tex.push_back(new Texture("asset/1.png", PNG));
	score_tex.push_back(new Texture("asset/2.png", PNG));
	score_tex.push_back(new Texture("asset/3.png", PNG));
	score_tex.push_back(new Texture("asset/4.png", PNG));
	score_tex.push_back(new Texture("asset/5.png", PNG));

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

	auto p1_score = AddGameObject<SpriteRenderer>(_2D);
	p1_score->Name = "Player1_Score";
	p1_score->SetSize(glm::vec2(100, 200));
	p1_score->Position = glm::vec3(100,50,0);
	p1_score->SetTexture(score_tex[0]);
	p1_score->mActive = false;

	auto p2_score = AddGameObject<SpriteRenderer>(_2D);
	p2_score->Name = "Player2_Score";
	p2_score->SetSize(glm::vec2(100, 200));
	p2_score->Position = glm::vec3(SCREEN_WIDTH - 200, 50, 0);
	p2_score->SetTexture(score_tex[0]);
	p2_score->mActive = false;

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

	for (int i = 0; i < 5; i++) {
		delete score_tex[i];
		score_tex[i] = nullptr;
	}
	score_tex.clear();
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

		// TODO: ç≈ìKâª
		GetGameObjectWithName<SpriteRenderer>(_2D, "Player1_Score")->SetTexture(score_tex[p1_score]);
		GetGameObjectWithName<SpriteRenderer>(_2D, "Player2_Score")->SetTexture(score_tex[p2_score]);
	}

	if (!mGameActive && glfwGetKey(GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		mGameActive = true;
		auto obj = GetGameObjectWithName<SpriteRenderer>(_2D, "Title_logo");
		obj->Destroy();
		GetGameObjectWithName<SpriteRenderer>(_2D, "Player1_Score")->mActive = true;
		GetGameObjectWithName<SpriteRenderer>(_2D, "Player2_Score")->mActive = true;
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

