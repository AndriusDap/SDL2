#pragma once
#include "Includes.h"
#include "Graphics.h"
#include "ILevel.h"
#include "Input.h"

using namespace std;

class LevelManager
{
private:
	vector<unique_ptr<ILevel>> levels;
	Input input;

public:
	LevelManager(Graphics &g);
	void Start(Graphics &g);
	void AppendLevel(unique_ptr<ILevel> level);
	~LevelManager(void);
};

