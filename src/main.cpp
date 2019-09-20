#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "camera.h"
#include "cube.h"

using namespace glm;
using namespace std;

const int window_width = 800;
const int window_height = 600;
float deltaTime;
float lastFrame;

float lastX = window_width / 2.0f;
float lastY = window_height / 2.0f;

float cameraSpeed = 0.05f;
GLFWwindow* window;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Cube* cubes[10];

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

void Init();
void UpdateLoop();
void InitDrawing();
void UpdateDrawing(float DeltaTime);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
void ProcessInput(GLFWwindow *window);
void Cleanup();

void InitDrawing()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	vec3 cubePositions[] = {
		vec3( 0.0f,  0.0f,  0.0f),
		vec3( 2.0f,  5.0f, -15.0f), 
		vec3(-1.5f, -2.2f, -2.5f),  
  		vec3(-3.8f, -2.0f, -12.3f),  
  		vec3( 2.4f, -0.4f, -3.5f),  
  		vec3(-1.7f,  3.0f, -7.5f),  
  		vec3( 1.3f, -2.0f, -2.5f),  
  		vec3( 1.5f,  2.0f, -2.5f), 
  		vec3( 1.5f,  0.2f, -1.5f), 
  		vec3(-1.3f,  1.0f, -1.5f)  
	};

	for(int i = 0; i < 10; ++i)
	{
		cubes[i] = new Cube("./shaders/basic.vs", "./shaders/basic.frag", "container.jpg", cubePositions[i]);
	}
} // InitDrawing()

void UpdateDrawing(float DeltaTime)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mat4 projection = perspective(radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
	for(int i = 0; i < 10; ++i)
	{
		cubes[i]->ProjectionMatrix = projection;
		cubes[i]->ViewMatrix = camera.GetViewMatrix();
		cubes[i]->Draw(DeltaTime);
	}
} // UpdateDrawning

int main()
{
	Init();
	InitDrawing();
	UpdateLoop();
	Cleanup();

	return 0;
} // main

void Init()
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //WindowTest = (WindowInfo*) malloc(sizeof(WindowTest));
	window = glfwCreateWindow(window_width, window_height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		//std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
		return;
	}
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer : " << renderer << endl;
	cout << "OpenGL version : " << version << endl;    
} // Init

void ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void UpdateLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(window);
        UpdateDrawing(deltaTime);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
} // UpdateLoop

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
} // FramebufferSizeCallback

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
} // MouseCallback

void Cleanup()
{
	glfwTerminate();
	for(int i = 0; i < 10; ++i)
	{
		cubes[i]->Cleanup();
		delete cubes[i];
	}
	//delete cube1;
} // Cleanup