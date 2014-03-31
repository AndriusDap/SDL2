#pragma once
#define GLFW_INCLUDE_GL_3
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <intrin.h>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <fstream>
#include <cassert>
#include <algorithm>
#include <future>
using namespace std;

#pragma comment(lib, "C:/Users/Andrius/Documents/Visual Studio 2012/Projects/SDL2/external/lib/Win32/glew32.lib")
#pragma comment(lib, "C:/Users/Andrius/Documents/Visual Studio 2012/Projects/SDL2/external/lib/Win32/glfw3dll.lib")   
#pragma comment(lib, "opengl32.lib")

const double PI = 3.141592653589793;

#define CheckGlErrors() \
{\
	int _line = __LINE__;\
	int _error = glGetError();\
	if(_error != 0)\
	{\
		printf("%s %d: %X\n",__FILE__, _line-1, _error);\
	/*	DebugBreak();*/\
	}\
}


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;