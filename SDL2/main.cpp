#pragma once
#include "Includes.h"
#include "Graphics.h"
#include "GLHelper.h"
#include "BasicEffect.h"
#include "PlayerShip.h"
#include "LevelManager.h"
#include "EmptyLevel.h"
#include "MenuLevel.h"
using namespace std;

int main(int argc, char *argv[])
{
	


	Graphics g(SCREEN_WIDTH, SCREEN_HEIGHT);	
	LevelManager levelManager(g);
	levelManager.AppendLevel(unique_ptr<ILevel>(new MenuLevel()));

	levelManager.Start(g);
	return 0;
}