#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <algorithm>
#include <list>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <SOIL/SOIL.h>

#include <Imgui/imgui.h>
#include <Imgui/imgui_impl_opengl3.h>
#include <Imgui/imgui_impl_glfw.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "SOIL.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include "Application.h"
#include "Shader.h"
#include "Im.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

GLFWwindow* GetWindow();
Application* GetApp();