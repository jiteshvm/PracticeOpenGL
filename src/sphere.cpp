#include "sphere.h"

using namespace glm;

Sphere::Sphere(float radius, unsigned int numSectors, unsigned int numStacks)
{
	
	this->sectorCount = numSectors;
	this->stackCount = numStacks;
	this->radius = radius;
    
	buildVerticesSmooth();
    printSelf();

	//interleavedVertices.push_back(0.5f);
	//interleavedVertices.push_back(0.5f);
	//interleavedVertices.push_back(0.0f);

	//interleavedVertices.push_back(0.5f);
	//interleavedVertices.push_back(-0.5f);
	//interleavedVertices.push_back(0.0f);

	//interleavedVertices.push_back(-0.5f);
	//interleavedVertices.push_back(-0.5f);
	//interleavedVertices.push_back(0.0f);

	//interleavedVertices.push_back(-0.5f);
	//interleavedVertices.push_back(0.5f);
	//interleavedVertices.push_back(0.0f);

	//indices.push_back(0);
	//indices.push_back(1);
	//indices.push_back(3);
	//indices.push_back(1);
	//indices.push_back(2);
	//indices.push_back(3);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// interleaved vertex buffer
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, interleavedVertices.size() * sizeof(float), interleavedVertices.data(), GL_STATIC_DRAW);
	
	// index buffer
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sphere::buildVerticesSmooth()
{
    const float PI = 3.1415926f;

    // clear memory of prev arrays
    vector<float>().swap(vertices);
    vector<float>().swap(normals);
    vector<float>().swap(texCoords);
    vector<unsigned int>().swap(indices);

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
    float s, t;                                     // texCoord

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for(unsigned int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(unsigned int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);

            // vertex tex coord between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            texCoords.push_back(s);
			texCoords.push_back(t);
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for(unsigned int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if(i != 0)
            {
                indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1+1);   // k1---k2---k1+1
            }

            if(i != (stackCount-1))
            {
                indices.push_back(k1+1);
				indices.push_back(k2);
				indices.push_back(k2+1); // k1+1---k2---k2+1
            }

            // vertical lines for all stacks
            //lineIndices.push_back(k1);
            //lineIndices.push_back(k2);
            //if(i != 0)  // horizontal lines except 1st stack
            //{
            //   lineIndices.push_back(k1);
            //    lineIndices.push_back(k1 + 1);
			//}
        }
    }

    // generate interleaved vertex array as well
    buildInterleavedVertices();
}

void Sphere::buildInterleavedVertices()
{
    vector<float>().swap(interleavedVertices);

    size_t i, j;
    size_t count = vertices.size();
    for(i = 0, j = 0; i < count; i += 3, j += 2)
    {
        interleavedVertices.push_back(vertices[i]);
        interleavedVertices.push_back(vertices[i+1]);
        interleavedVertices.push_back(vertices[i+2]);

        interleavedVertices.push_back(normals[i]);
        interleavedVertices.push_back(normals[i+1]);
        interleavedVertices.push_back(normals[i+2]);

        interleavedVertices.push_back(texCoords[j]);
        interleavedVertices.push_back(texCoords[j+1]);
    }
}

void Sphere::printSelf() const
{
	cout << "===== Sphere =====\n"
		<< "        Radius: " << radius << "\n"
		<< "  Sector Count: " << sectorCount << "\n"
		<< "   Stack Count: " << stackCount << "\n"
		<< "Triangle Count: " << indices.size() / 3 << "\n"
		<< "   Index Count: " << indices.size() << "\n"
		<< "  Vertex Count: " << vertices.size() / 3 << "\n"
		<< "  Normal Count: " << normals.size() / 3 << "\n"
		<< "TexCoord Count: " << texCoords.size() / 2 << endl;
}

void Sphere::Update(float DeltaTime)
{
	Super::Update(DeltaTime);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glDrawElements(	GL_TRIANGLES, (unsigned int) indices.size(), GL_UNSIGNED_INT, 0);
}

void Sphere::Cleanup()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &index_buffer);
	Super::Cleanup();
}
