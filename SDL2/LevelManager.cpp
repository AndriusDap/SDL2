#include "LevelManager.h"


LevelManager::LevelManager(void)
{
}


LevelManager::~LevelManager(void)
{
}

void LevelManager::Start(Graphics &g)
{
	size_t currentLevel = 0;
	bool stop = false;
	
	const int TICKS_PER_SECOND = 120;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 10;

	int nextLevelTick = clock();
	int loops;
	int lastGameTick = clock();
	
	levels[currentLevel]->Initialize(g, input);
	int changeLevel = 0;
	while(!input.Quit){
		loops = 0;		
		
		while(clock() > nextLevelTick && loops < MAX_FRAMESKIP && !changeLevel)
		{
			int now = clock();
			input.Update(now - lastGameTick);
			
			changeLevel = levels[currentLevel]->Update(now - lastGameTick);
			switch(changeLevel)
			{
			case 1:
				{
					levels[currentLevel]->CleanUp(g);
					currentLevel++;
					if(currentLevel != levels.size())
					{
						currentLevel = 0;
						levels[currentLevel]->Initialize(g, input);
						break;
					}
				}
			case -1:
				{
					levels[currentLevel]->CleanUp(g);
					currentLevel = 0;
					levels[0]->Initialize(g, input);
					break;
				}
			}
			lastGameTick = now;
			nextLevelTick += SKIP_TICKS;
			loops++;
		}		

		levels[currentLevel]->Render(g);
		g.Flip();
	}

}

void LevelManager::AppendLevel(unique_ptr<ILevel> level)
{
	levels.emplace_back(move(level));
}