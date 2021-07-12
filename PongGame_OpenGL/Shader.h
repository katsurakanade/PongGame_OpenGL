#pragma once

enum class ShaderGroup {
	Default,
	Light,
	Sprite
};

class Shader
{

private:
	
	static GLuint programID;
	static GLuint light_programID;
	static GLuint sprite_programID;

public :

	static void Init(ShaderGroup target);
	static void Use(ShaderGroup target);
	static void Uninit();
	static GLint FindUniform(ShaderGroup group, const char* target);

	static GLuint GetprogramID() { return programID; };
};

