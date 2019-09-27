#ifndef SPHERE_H
#define SPHERE_H

#include <glad/glad.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "shader.h"
#include <vector>

const unsigned int NUM_SECTORS = 36;
const unsigned int NUM_STACKS = 18;

class Sphere
{
public:

	Sphere(float radius, unsigned int numSectors = NUM_SECTORS, unsigned int numStacks = NUM_STACKS);
	void Draw(float DeltaTime);
	void Cleanup();
	void SetShaders(const char* vertexPath, const char* fragmentPath);
	glm::mat4 ModelMatrix = glm::mat4(1.0f);
	glm::mat4 ViewMatrix = glm::mat4(1.0f);
	glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

private:
	float radius;
	unsigned int sectorCount;
	unsigned int stackCount;
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	std::vector<unsigned int> indices;
	std::vector<float> interleavedVertices;
	Shader* shader;
	GLuint VAO;
	GLuint vertex_buffer;
	GLuint index_buffer;
	GLint attribVertexPosition;
	GLint attribVertexNormal;
	GLint attribVertexTexCoord;
	glm::vec3 position = glm::zero<glm::vec3>();

	void buildVerticesSmooth();
	void buildInterleavedVertices();
	void printSelf() const;
};
#endif

