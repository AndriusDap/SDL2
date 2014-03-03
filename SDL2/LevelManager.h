#pragma once
#include "Includes.h"
#include "Graphics.h"
#include "ILevel.h"
#include "Input.h"
#include <vector>
#include <memory>
using namespace std;

class LevelManager
{
private:
	vector<unique_ptr<ILevel>> levels;
	Input input;
public:
	LevelManager(void);
	void Start(Graphics &g);
	void AppendLevel(unique_ptr<ILevel> level);
	~LevelManager(void);
};

