#include "cube.h"
#include <iostream>

using namespace glm;

Cube::Cube()
{
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


    //SetRandomRotationAxis();
}

//void Cube::SetRandomRotationAxis()
//{
//    randomRotationAxis.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//	randomRotationAxis.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//	randomRotationAxis.z = 1.0f;
//}

void Cube::Update(float DeltaTime)
{
	Super::Update(DeltaTime);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::Cleanup()
{
	Super::Cleanup();
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
