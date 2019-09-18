#include "windowhandler.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Shader* ourShader;
unsigned int VAO;
unsigned int VBO;
unsigned int EBO;
unsigned int texture;
glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
  		glm::vec3(-3.8f, -2.0f, -12.3f),  
  		glm::vec3( 2.4f, -0.4f, -3.5f),  
  		glm::vec3(-1.7f,  3.0f, -7.5f),  
  		glm::vec3( 1.3f, -2.0f, -2.5f),  
  		glm::vec3( 1.5f,  2.0f, -2.5f), 
  		glm::vec3( 1.5f,  0.2f, -1.5f), 
  		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};

glm::vec3 randomAxisRotations[10];

void update();

int main()
{
	initWindow(800, 600);
	glEnable(GL_DEPTH_TEST);

	float cube_vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	for(unsigned int i = 0; i < 10; ++i)
	{
		randomAxisRotations[i].x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		randomAxisRotations[i].y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		randomAxisRotations[i].z = 1.0f;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// load and create a texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int tex_width, tex_height, nrchannels;
	stbi_set_flip_vertically_on_load(true);
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
	
	// color and texture
	int vertexColorLocation = glGetUniformLocation(ourShader->ID, "uniformColor");
	glUniform4f(vertexColorLocation, 0.0f, 1.0, 0.0f, 1.0f);
	int textureLocation = glGetUniformLocation(ourShader->ID, "texture2");
	glUniform1i(textureLocation, 0);


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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		ourShader->use();

		// mvp matrix
		glm::mat4 view_mat = glm::mat4(1.0f);
		glm::mat4 projection_mat = glm::mat4(1.0f);
		
		view_mat = glm::translate(view_mat, glm::vec3(0.0f, 0.0f, -5.0f));
		projection_mat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		

		glBindVertexArray(VAO);
		for(unsigned int i = 0; i < 10; ++i)
		{
			glm::mat4 model_mat = glm::mat4(1.0f);
			model_mat = glm::translate(model_mat, cubePositions[i]);
			model_mat = glm::rotate(model_mat, (float)glfwGetTime(), randomAxisRotations[i]);		
			glm::mat4 mvp_mat = projection_mat * view_mat * model_mat;
			int mvpLoc = glGetUniformLocation(ourShader->ID, "mvp_mat");
			glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp_mat));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
}