#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "main.h"
#include "Texture.h"

Texture::Texture(const char* pass,TEXTURE_TYPE type) {

	unsigned char* pixels = nullptr;

	if (type == TEXTURE_TYPE::JPG) {
		pixels = stbi_load(pass, &width, &height, &channels, 0);
	}
	else if (type == TEXTURE_TYPE::PNG) {
		pixels = stbi_load(pass, &width, &height, &channels, STBI_rgb_alpha);
	}

	if (pixels) {
		std::cout << "Image Loaded : " << pass << std::endl;
	}
	else {
		std::cout << "Image Load Failed : " << pass << std::endl;
	}

	glGenTextures(1, &data);
	glBindTexture(GL_TEXTURE_2D, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	if (type == TEXTURE_TYPE::JPG) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	}

	else if (type == TEXTURE_TYPE::PNG) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	}

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, data);
}
