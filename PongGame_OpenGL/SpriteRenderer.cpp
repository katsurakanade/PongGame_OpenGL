#include "main.h"
#include "SpriteRenderer.h"

static GLfloat vertices[] = {
    // Pos      // Tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
};

void SpriteRenderer::Init() {

    VAO = new GLuint;
    vertexbuffer = new GLuint;

    glGenVertexArrays(1, this->VAO);
    glGenBuffers(1, vertexbuffer);

    glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindVertexArray(*VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Size.x = 100.0f;
    Size.y = 100.0f;

    Position = glm::vec3(0, 0, 0);
    color = glm::vec3(1.0f, 1.0f, 1.0f);
}

void SpriteRenderer::Uninit() {
    delete VAO;
    delete vertexbuffer;
}

void SpriteRenderer::Update() {


   
}

void SpriteRenderer::Draw() {

    Shader::Use(ShaderGroup::Sprite);
    glm::mat4 model;
    model = glm::translate(model, Position);  

    model = glm::translate(model, glm::vec3(0.5f * Size.x, 0.5f * Size.y, 0.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * Size.x, -0.5f * Size.y, 0.0f)); 
    model = glm::scale(model, glm::vec3(Size, 1.0f)); 

    glUniformMatrix4fv(Shader::FindUniform(ShaderGroup::Sprite, "model"), 1, GL_FALSE, glm::value_ptr(model));
   
    glUniform3f(Shader::FindUniform(ShaderGroup::Sprite, "spriteColor"), color.x, color.y, color.z);

   
    if (texture) {
        glActiveTexture(GL_TEXTURE0);
        texture->Bind();
    }

    glBindVertexArray(*VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::SetTexture(Texture* data) {
    this->texture = data;
}