#include "MasterObject.h"
#include <string>
#include <fstream>
#include <cassert>
#include <vector>
using namespace std;

MasterObject::MasterObject(void)
{
	vertices = NULL;
	drawSequence = NULL;
}



void MasterObject::LoadMesh(string filePath){
	ifstream file(filePath);
	assert(file.is_open());

	vector<float> vert;
	vector<int> sequ;

	while(!file.eof()){
		string lineType;
		file >> lineType;
		
		if(lineType == "v" || lineType == "V"){
			//vertex. Read three floats to vertices array
			float tmp;
			for(int i = 0; i < 3; i++){
				file >> tmp;
				vert.push_back(tmp);
			}
		} else if(lineType == "f" || lineType == "F"){
			//drawSequence. Read three ints to draw sequence array
			int tmp;
			for(int i = 0; i < 3; i++){
				file >> tmp;
				sequ.push_back(tmp - 1);
			}
		} else {
			//Other line types are not yet implemented. Skip them
			string line;
			getline(file, line);
		}
	}

	vertices = new float[vert.size()];
	verticesLength = vert.size();
	drawSequence = new int[sequ.size()];
	drawSequenceLength = sequ.size();
}

GLuint MasterObject::getVertices(GLenum usage){
	GLuint buffer;
	gl::GenBuffers(1, &buffer);
	gl::BindBuffer(gl::ARRAY_BUFFER, buffer);
	gl::BufferData(gl::ARRAY_BUFFER, verticesLength * sizeof(float), vertices, usage);
	return buffer;
}



GLuint MasterObject::getDrawSequence(){
	GLuint buffer;
	gl::GenBuffers(1, &buffer);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffer);
	gl::BufferData(gl::ARRAY_BUFFER, drawSequenceLength * sizeof(int), drawSequence, gl::STATIC_DRAW);
	return buffer;
}

unsigned int MasterObject::getVerticesCount(){
	return verticesLength;
}

unsigned int MasterObject::getTriangleCount(){
	return drawSequenceLength/3;
}

MasterObject::~MasterObject(void){
	if(vertices)
		delete[] vertices;
	if(drawSequence)
		delete[] drawSequence;
}
