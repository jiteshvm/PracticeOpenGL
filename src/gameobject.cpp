#include "gameobject.h"

#include <stb/stb_image.h>

void GameObject::Update(float DeltaTime)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mainTexture);
	shader->use();
	
	// mvp matrix
	ModelMatrix = mat4(1.0f);
	ModelMatrix = translate(ModelMatrix, Position);
	//ModelMatrix = rotate(ModelMatrix, (float)ElapsedTime, randomRotationAxis);
	int modelLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(ModelMatrix));

	int viewLoc = glGetUniformLocation(shader->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(ViewMatrix));

	int projectionLoc = glGetUniformLocation(shader->ID, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(ProjectionMatrix));

	mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
	int mvpLoc = glGetUniformLocation(shader->ID, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, value_ptr(mvp));
}

void GameObject::Cleanup()
{
	delete shader;
}

void GameObject::SetShaders(const char * vertexPath, const char * fragmentPath)
{
	if (shader != nullptr)
	{
		delete shader;
	}
	shader = new Shader(vertexPath, fragmentPath);
	shader->use();
}

void GameObject::SetTexture(const char * texturePath)
{
	if (texturePath != nullptr)
	{
		// load and create a texture
		glGenTextures(1, &mainTexture);
		glBindTexture(GL_TEXTURE_2D, mainTexture);

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

		if (shader != nullptr)
		{
			int textureLocation = glGetUniformLocation(shader->ID, "mainTexture");
			glUniform1i(textureLocation, 0);
			
		}
		
	}
}
