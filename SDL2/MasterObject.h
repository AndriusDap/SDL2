#pragma once
#include <memory>
#include <string>
#include <glload\gl_4_2.hpp>

class MasterObject
{
private:
	float* vertices;
	unsigned int verticesLength;
	int* drawSequence;
	unsigned int drawSequenceLength;

public:
	MasterObject(void);
	void LoadMesh(std::string filePath);
	GLuint getVertices(GLenum usage);
	unsigned int getVerticesCount();
	GLuint getDrawSequence();
	unsigned int getTriangleCount();
	~MasterObject(void);
};

