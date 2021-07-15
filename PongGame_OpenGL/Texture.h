#pragma once

enum TEXTURE_TYPE {
	JPG,PNG
};

class Texture
{
private:

	GLuint data;
	int width;
	int height;
	int channels;

public:

	Texture(const char* pass, TEXTURE_TYPE type);

	void Bind();

	void ConvertToBinary(const char* path,std::string output_path, TEXTURE_TYPE type);
};

