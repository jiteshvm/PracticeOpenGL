#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

using namespace glm;

class GameObject
{
protected:
	//GameObject();
	Shader* shader;
	virtual void Update(float DeltaTime);
	virtual void Cleanup();
	GLuint mainTexture;

public:
	
	typedef GameObject Super;

	mat4 ModelMatrix = mat4(1.0f);
	mat4 ViewMatrix = mat4(1.0f);
	mat4 ProjectionMatrix = mat4(1.0f);

	vec3 Position = zero<vec3>();
	vec3 Rotation = zero<vec3>();
	vec3 Scale = one<vec3>();
	void SetShaders(const char* vertexPath, const char* fragmentPath);
	void SetTexture(const char* texturePath);
};

#endif
