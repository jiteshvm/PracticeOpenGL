#include "windowhandler.h"

int window_width;
int window_height;
GLFWwindow* window;

void initWindow(int width, int height)
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //WindowTest = (WindowInfo*) malloc(sizeof(WindowTest));
	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		//std::cout << "Failed to create GLFW window" << std::endl;
		terminateWindow();
		return;
	}
    window_width = width;
    window_height = height;
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//std::cout << "Failed to initialize GLAD" << std::endl;
        terminateWindow();
		return;
	}
	//const GLubyte* renderer = glGetString(GL_RENDERER);
	//const GLubyte* version = glGetString(GL_VERSION);
	//std::cout << "Renderer : " << renderer << std::endl;
	//std::cout << "OpenGL version : " << version << std::endl;    
}

void updateWindow(void (*update)())
{
    while (!glfwWindowShouldClose(window))
	{
		processInput(window);
        update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void terminateWindow()
{
    glfwTerminate();
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
    window_width = width;
    window_height = height;
	glViewport(0, 0, width, height);
}