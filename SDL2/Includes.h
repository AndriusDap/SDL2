#pragma once
#include <string>
#include <intrin.h>
#include <SDL.h>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <iostream>
#include <glload\gl_4_3.hpp>
#include <glload\gl_load.hpp>
#include <unordered_map>
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <fstream>
#include <cassert>
using namespace std;

const double PI = 3.141592653589793;

#define CheckGlErrors() \
{\
	int _line = __LINE__;\
	int _error = gl::GetError();\
	if(_error != 0)\
	{\
		printf("%d: %X\n",_line-1, _error);\
		DebugBreak();\
	}\
}


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;