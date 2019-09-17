#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void initWindow(int width, int height);
void updateWindow(void (*update)());
void terminateWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

 #endif