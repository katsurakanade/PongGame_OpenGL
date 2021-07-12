#include "main.h"
#include "Shader.h"
#include "Cube.h"

GLfloat vertices[] = {

	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

GLuint indices[] = {  // Note that we start from 0!
	   0, 1, 3, // First Triangle
	   1, 2, 3  // Second Triangle
};

void Cube::Init() {

	VAO = new GLuint;

	vertexbuffer = new GLuint;

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(*VAO);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	color = glm::vec3(1.0f, 1.0f, 1.0f);

	material.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	material.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	material.shininess = 64.0f;

}

void Cube::Uninit() {

	
}

void Cube::Update() {

	if (glfwGetKey(GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS && is_light) {
		Position.z += 0.5f;
	}

	if (glfwGetKey(GetWindow(), GLFW_KEY_UP) == GLFW_PRESS && is_light) {
		Position.z -= 0.5f;
	}

	if (glfwGetKey(GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS && is_light) {
		Position.x += 0.5f;
	}

	if (glfwGetKey(GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS && is_light) {
		Position.x -= 0.5f;
	}

	if (glfwGetKey(GetWindow(), GLFW_KEY_T) == GLFW_PRESS && is_light) {
		Position.y += 0.5f;
	}

	if (glfwGetKey(GetWindow(), GLFW_KEY_B) == GLFW_PRESS && is_light) {
		Position.y -= 0.5f;
	}

	if (glfwGetKey(GetWindow(), GLFW_KEY_E) == GLFW_PRESS && is_light) {
		Scale += glm::vec3(0.1f,0.1f,0.1f);
	}

	if (glfwGetKey(GetWindow(), GLFW_KEY_Q) == GLFW_PRESS && is_light) {
		Scale -= glm::vec3(0.1f, 0.1f, 0.1f);
	}
	
	if (glfwGetKey(GetWindow(), GLFW_KEY_Z) == GLFW_PRESS && is_light) {
		Rotation -= glm::vec3(0.0f, 0.5f, 0.0f);
	}

	if (glfwGetKey(GetWindow(), GLFW_KEY_C) == GLFW_PRESS && is_light) {
		Rotation += glm::vec3(0.0f, 0.5f, 0.0f);
	}
}

void Cube::Draw(Type type,Cube light) {
	
	glm::mat4 model;
	glm::quat q = glm::quat(glm::radians(glm::vec3(Rotation.x, Rotation.y, Rotation.z)));

	model = glm::translate(model, Position);

	if (is_light) {
		
		model = glm::mat4_cast(q) * model;
	}

	model = glm::scale(model, Scale);

	if (type == Type::Default) {

		Shader::Use(ShaderGroup::Default);

		glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Default, "model"), 1, GL_FALSE, glm::value_ptr(model));
	
		glUniform3f(Shader::FindUniform(ShaderGroup::Default, "BaseColor"), color.x, color.y, color.z);

		glUniform3f(Shader::FindUniform(ShaderGroup::Default, "material.ambient"), material.ambient.x, material.ambient.y, material.ambient.z);
		glUniform3f(Shader::FindUniform(ShaderGroup::Default, "material.diffuse"), material.diffuse.x, material.diffuse.y, material.diffuse.z);
		glUniform3f(Shader::FindUniform(ShaderGroup::Default, "material.specular"), material.specular.x, material.specular.y, material.specular.z);
		glUniform1f(Shader::FindUniform(ShaderGroup::Default, "material.shininess"), material.shininess);

		glUniform3f(Shader::FindUniform(ShaderGroup::Default, "light.position"), light.Position.x, light.Position.y, light.Position.z);
		glUniform3f(Shader::FindUniform(ShaderGroup::Default, "light.ambient"), 0.5f, 0.5f, 0.5f);
		glUniform3f(Shader::FindUniform(ShaderGroup::Default, "light.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(Shader::FindUniform(ShaderGroup::Default, "light.specular"), 1.0f, 1.0f, 1.0f);
	}

	else if (type == Type::Light) {

		Shader::Use(ShaderGroup::Light);
		glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Light, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(Shader::FindUniform(ShaderGroup::Light, "objectcolor"), color.x, color.y, color.z);
		glUniform3f(Shader::FindUniform(ShaderGroup::Light, "lightcolor"), 1.0f, 1.0f, 1.0f);
	}

	if (texture) {
		
		glActiveTexture(GL_TEXTURE0);
		texture->Bind();
	}

	glBindVertexArray(*VAO);
	
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}

void Cube::SetTexture(Texture* data) {
	this->texture = data;
}