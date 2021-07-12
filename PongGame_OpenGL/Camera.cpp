#include "main.h"
#include "Camera.h"

void Camera::Init(){

	Position = glm::vec3(0.0f, 0.0f, 15.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

}

void Camera::Uninit() {

}

void Camera::Update() {


	if (glfwGetKey(GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		Rotation.x = 0.0f;
		Rotation.y = 0.0f;
		Rotation.z = 0.0f;
	}

	view = glm::lookAt(Position, Position + front, up);
	view = glm::rotate(view, Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::scale(view, Scale);

	projection = glm::perspective(45.0f, (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);
	projection2d = glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH), static_cast<GLfloat>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

	model = glm::translate(model, Position);
	model = glm::rotate(model, Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, Scale);

}

void Camera::Draw() {

}

void Camera::SetCamera(int type) {

	if (type == 0) {
		glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Default, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Default, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Default, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3f(Shader::FindUniform(ShaderGroup::Default, "viewpos"), Position.x, Position.y, Position.z);
	}

	else if (type == 1) {
		glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Light, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Light, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Light, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	}

	else if (type == 2) {
		glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Sprite, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Sprite, "projection"), 1, GL_FALSE, glm::value_ptr(projection2d));
	}
}