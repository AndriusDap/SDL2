#include "Includes.h"
#include "LevelManager.h"
#include "EmptyLevel.h"
#include "MenuLevel.h"

LevelManager::LevelManager(Graphics &g)
	: input(g.main_window)
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
	long frameCount = 0;
	int startTime = clock();

	while(!input.Quit){
		loops = 0;		
		frameCount++;
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
					if(currentLevel == levels.size())
					{
						levels.push_back(unique_ptr<ILevel>(new EmptyLevel()));
						levels.push_back(unique_ptr<ILevel>(new MenuLevel()));
					}
					levels[currentLevel]->Initialize(g, input);
					changeLevel = 0;
					break;
				}
			case -1:
				{
					levels[currentLevel]->CleanUp(g);
					currentLevel = 0;
					levels[0]->Initialize(g, input);
					changeLevel = 0;
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
	int endTime = clock();
//	OutputDebugString(to_wstring(((double) endTime - startTime)/frameCount).c_str());
//	OutputDebugString(L"\r\n");
}

void LevelManager::AppendLevel(unique_ptr<ILevel> level)
{
	levels.emplace_back(move(level));
}