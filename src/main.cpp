#include "windowhandler.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

Shader* ourShader;
unsigned int VAO;
unsigned int VBO;
unsigned int EBO;
unsigned int texture;

void update();

int main()
{
	initWindow(800, 600);
	int tex_width;
	int tex_height;
	int nrchannels;

	
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture);

	unsigned char* texture_data = stbi_load("container.jpg", &tex_width, &tex_height, &nrchannels, 0);

	if (texture_data) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(texture_data);

	ourShader = new Shader("./shaders/basic.vs", "./shaders/basic.frag");
	ourShader->use();
	int vertexColorLocation = glGetUniformLocation(ourShader->ID, "uniformColor");
	int textureLocation = glGetUniformLocation(ourShader->ID, "texture2");
	glUniform4f(vertexColorLocation, 0.0f, 1.0, 0.0f, 1.0f);
	glUniform1i(textureLocation, 1);
	
	float vertices[] = {
		// positions         // colors
		0.5f , -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // bottom left
		-0.5f, 0.5f , 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  // top left
		0.5f , 0.5f , 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f  // top right
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	updateWindow(update);

	terminateWindow();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete ourShader;
	
	return 0;
}

void update()
{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader->use();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}