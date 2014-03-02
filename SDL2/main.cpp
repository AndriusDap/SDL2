#pragma once
#include <ctime>
#include "Includes.h"
#include "Graphics.h"
#include "MasterObject.h"
#include "GLHelper.h"
#include "BasicEffect.h"
#include "PlayerShip.h"

using namespace std;

int main(int argc, char *argv[])
{
	Graphics g(SCREEN_WIDTH, SCREEN_HEIGHT);	
	
	bool stop = false;
	Input input;
	PlayerShip ship(&input);

	const int TICKS_PER_SECOND = 120;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 10;

	int next_game_tick = clock();
	int loops;
	int last_update = clock();

	while(!input.Quit){
		loops = 0;		
		
		while(clock() > next_game_tick && loops < MAX_FRAMESKIP)
		{
			int now = clock();
			input.Update(now - last_update);
			ship.Update(now - last_update);			
			last_update = now;
			next_game_tick += SKIP_TICKS;
			loops++;
		}		
		ship.Render(g);		
		g.Flip();
	}
	
	return 0;
}