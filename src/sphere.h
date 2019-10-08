#ifndef SPHERE_H
#define SPHERE_H

#include "shader.h"
#include "gameobject.h"

#include <vector>

const unsigned int NUM_SECTORS = 36;
const unsigned int NUM_STACKS = 18;

using namespace std;

class Sphere : public GameObject
{
public:

	Sphere(float radius, unsigned int numSectors = NUM_SECTORS, unsigned int numStacks = NUM_STACKS);
	void Update(float DeltaTime) override;
	void Cleanup() override;

private:
	float radius;
	unsigned int sectorCount;
	unsigned int stackCount;
	vector<float> vertices;
	vector<float> normals;
	vector<float> texCoords;
	vector<unsigned int> indices;
	vector<float> interleavedVertices;
	GLuint VAO;
	GLuint vertex_buffer;
	GLuint index_buffer;
	//GLint attribVertexPosition;
	//GLint attribVertexNormal;
	//GLint attribVertexTexCoord;

	void buildVerticesSmooth();
	void buildInterleavedVertices();
	void printSelf() const;
};
#endif

