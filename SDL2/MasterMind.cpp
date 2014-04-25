#include "Includes.h"
#include "MasterMind.h"

void MasterMind::MoveBots(vector<shared_ptr<StupidBot>> bots, glm::vec2 PlayerPosition)
{
	for(size_t i = 0; i < bots.size(); i++)
	{
		auto current = bots[i];
		glm::vec2 position(0, 0);
		float hate = 0.1f;
		if(bots.size() > 10)
		{
			hate = 1.0f / bots.size();
		}
		auto fun = [&](glm::vec2 pos, glm::vec2 pos2, float maxdistance)
			{
				float dist = glm::distance(current->position, pos2);
				float force = sqrt((maxdistance - dist) / maxdistance);
				if(force != force) 
				{
					force = 0;
				}
				return (current->position - pos2) * force;
			};

		for(size_t j = 0; j < bots.size(); j++)
		{
			if(j == i)
			{
				continue;
			}
			position += fun(position, bots[j]->position, 100);
		}
		auto res = fun(position, PlayerPosition, 1000);
		position -= res;
		position = position / ((float) bots.size());

		bots[i]->MoveTo(position);
	}
};