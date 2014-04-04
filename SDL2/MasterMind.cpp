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
			hate *= bots.size();
		}
		auto fun = [&](glm::vec2 pos, shared_ptr<StupidBot> bot)
			{
				float coef = pow(glm::distance(current->position, bot->position) * hate, -8.0f);
				return pos + (current->position - bot->position) * coef;
			};

		for(size_t j = 0; j < bots.size(); j++)
		{
			if(j == i)
			{
				continue;
			}
			position += fun(position, bots[j]);
		}

		position -= current->position - PlayerPosition;
		bots[i]->MoveTo(position);
	}
};