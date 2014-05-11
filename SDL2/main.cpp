#pragma once
#include "Includes.h"
#include "Graphics.h"
#include "GLHelper.h"
#include "BasicEffect.h"
#include "PlayerShip.h"
#include "LevelManager.h"
#include "EmptyLevel.h"
using namespace std;

int main(int argc, char *argv[])
{
	


	Graphics g(SCREEN_WIDTH, SCREEN_HEIGHT);	
	LevelManager levelManager(g);

	levelManager.AppendLevel(unique_ptr<ILevel>(new EmptyLevel()));
	levelManager.AppendLevel(unique_ptr<ILevel>(new EmptyLevel()));
	levelManager.AppendLevel(unique_ptr<ILevel>(new EmptyLevel()));
	levelManager.AppendLevel(unique_ptr<ILevel>(new EmptyLevel()));
	levelManager.AppendLevel(unique_ptr<ILevel>(new EmptyLevel()));
	levelManager.AppendLevel(unique_ptr<ILevel>(new EmptyLevel()));

	levelManager.Start(g);
	return 0;
}