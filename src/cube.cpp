#include "cube.h"
#include <stb/stb_image.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;

Cube::Cube(const char* vertexPath, const char* fragmentPath, const char* texturePath, const vec3 pos)
{
    position = pos;

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

    if(texturePath != nullptr)
    {
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
	    unsigned char* texture_data = stbi_load(texturePath, &tex_width, &tex_height, &nrchannels, 0);

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
    }
	

	ourShader = new Shader(vertexPath, fragmentPath);
	ourShader->use();
	int textureLocation = glGetUniformLocation(ourShader->ID, "texture2");
	glUniform1i(textureLocation, 0);
    glBindVertexArray(0);

    SetRandomRotationAxis();
}

void Cube::SetRandomRotationAxis()
{
    randomRotationAxis.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	randomRotationAxis.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	randomRotationAxis.z = 1.0f;
}
void Cube::Draw(float ElapsedTime)
{
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
    ourShader->use();
    // mvp matrix
    mat4 view_mat = mat4(1.0f);
	mat4 projection_mat = mat4(1.0f);
	view_mat = translate(view_mat, vec3(0.0f, 0.0f, -5.0f));
	projection_mat = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glBindVertexArray(VAO);
	mat4 model_mat = mat4(1.0f);
	model_mat = translate(model_mat, position);
	model_mat = rotate(model_mat, (float)ElapsedTime, randomRotationAxis);		
	mat4 mvp_mat = projection_mat * view_mat * model_mat;
    int mvpLoc = glGetUniformLocation(ourShader->ID, "mvp_mat");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, value_ptr(mvp_mat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete ourShader;
}
