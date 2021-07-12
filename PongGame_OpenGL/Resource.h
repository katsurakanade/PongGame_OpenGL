#pragma once

#include "main.h"

class Resource
{
private:

    bool Alive = true;

public:

    glm::vec3 Position = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Scale = glm::vec3(1.0f,1.0f,1.0f);
    glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f);
    std::string Name = "Object";
    bool mActive = true;
    

    virtual void Init() = 0;
    virtual void Uninit() = 0;
    virtual void UpdateCollision() {};
    virtual void Update() = 0;
    virtual void Draw() = 0;

    void Destroy() { this->Alive = false; };
    // íœi“à•”—pj
    bool Remove() {
        if (!Alive) {
            Uninit();
            delete this;
            return true;
        }
        else {
            return false;
        }
    }

    bool Hitcheck(glm::vec3 line_pos_0, glm::vec3 line_pos_1, glm::vec3 circle_pos, float radius);
};

