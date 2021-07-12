#include "main.h"
#include "Shader.h"

 GLuint Shader::programID;
 GLuint Shader::light_programID;
 GLuint Shader::sprite_programID;

void Shader::Init(ShaderGroup target) {

	char* vs_pass = (char*)"";
	char* fs_pass = (char*)"";

	switch (target){

		case ShaderGroup::Default:
			vs_pass = (char*)"VS.glsl";
			fs_pass = (char*)"FS.glsl";
			break;
		case ShaderGroup::Light:
			vs_pass = (char*)"LightVS.glsl";
			fs_pass = (char*)"LightFS.glsl";
			break;
		case ShaderGroup::Sprite:
			vs_pass = (char*)"VS2D.glsl";
			fs_pass = (char*)"FS2D.glsl";
		default:
			break;
	}

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vs_pass, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		std::cout << "File Not Fount" << std::endl;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fs_pass, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else {
		std::cout << "File Not Fount" << std::endl;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cout << &VertexShaderErrorMessage[0] << std::endl;
	}

	// Compile Fragment Shader
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cout << &FragmentShaderErrorMessage[0] << std::endl;
	}

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	switch (target) {

	case ShaderGroup::Default:
		programID = ProgramID;
		break;
	case ShaderGroup::Light:
		light_programID = ProgramID;
		break;
	case ShaderGroup::Sprite:
		sprite_programID = ProgramID;
		break;
	default:
		break;
	}


}

void Shader::Uninit() {


	
}

GLint Shader::FindUniform(ShaderGroup group,const char* target) {
	
	switch (group)
	{
	case ShaderGroup::Default:
		return glGetUniformLocation(programID, target);
		break;
	case ShaderGroup::Light:
		return glGetUniformLocation(light_programID, target);
		break;
	case ShaderGroup::Sprite:
		return glGetUniformLocation(sprite_programID, target);
		break;
	default:
		return -1;
		break;
	}

}

void Shader::Use(ShaderGroup target) {

	switch (target)
	{
	case ShaderGroup::Default:
		glUseProgram(programID);
		break;
	case ShaderGroup::Light:
		glUseProgram(light_programID);
		break;
	case ShaderGroup::Sprite:
		glUseProgram(sprite_programID);
		break;
	default:
		break;
	}

}
