//#include "main.h"
//#include "Light.h"
//
//void Light::Init(){
//
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//}
//
//void Light::Uninit() {
//
//}
//
//void Light::SetLight() {
//
//	glm::mat4 model;
//
//	model = glm::translate(model, Position);
//	model = glm::rotate(model, Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
//	model = glm::rotate(model, Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
//	model = glm::rotate(model, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
//	model = glm::scale(model, Scale);
//
//	glUniformMatrix4fv(Shader::FindUniform_Light("model"), 1, GL_FALSE, glm::value_ptr(model));
//
//	Shader::Use_Light();
//	glUniform3f(Shader::FindUniform_Light("objectcolor"), 1.0f, 0.5f, 0.31f);
//	glUniform3f(Shader::FindUniform_Light("lightcolor"), 1.0f, 1.0f, 1.0f);
//	glBindVertexArray(VAO);
//	glBindVertexArray(VBO);
//}
//
//void Light::Update() {
//	
//	
//}
//
//void Light::Draw() {

	//glBindVertexArray(VAO);
	//glm::mat4 model;
	//glUniformMatrix4fv(Shader::FindUniform_Light("model"), 1, GL_FALSE, glm::value_ptr(model));
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindVertexArray(0);
//}

