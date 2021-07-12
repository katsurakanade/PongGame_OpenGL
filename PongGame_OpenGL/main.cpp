#include "main.h"
#include "Application.h"

GLFWwindow* window;

void processInput(GLFWwindow* window);

Application* app;

int main() {

	srand(time(NULL));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	std::cout << "OpenGL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Im::Init();

	app = new Application();
	app->Init();
	
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		processInput(window);

		Im::Update();
		app->Update();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		app->Render();
		Im::Draw();

		glfwSwapBuffers(window);

	}

	app->Uninit();
	delete app;
	app = nullptr;
	Im::Uninit();

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
};

GLFWwindow* GetWindow() {
	return window;
}

Application* GetApp() {
	return app;
}