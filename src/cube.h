#ifndef CUBE_H
#define CUBE_H

#include "shader.h"
#include "gameobject.h"

class Cube : public GameObject
{
public:
	Cube();
	void Update(float DeltaTime) override;
    void Cleanup() override;
	//void SetRandomRotationAxis();

protected:
	float cube_vertices[288] = {
		//color					tex coords		normals
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f,		0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f,		0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		-1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,		0.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f,		 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		 0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		0.0f,  1.0f,  0.0f
	};

    unsigned int VAO;
    unsigned int VBO;
    //glm::vec3 randomRotationAxis;
	//float ElapsedTime;
};
#endif