#pragma once
#include "Model.hpp"

using namespace models;

class FPSCounter
{
	public:
		FPSCounter();
		~FPSCounter();
		void update(float deltaTime);
		//void draw(sf::RenderWindow* targetWindow);
	
	private:
		/*sf::Time updateTime;
		sf::Text* statsText;
		sf::Clock clock;*/
		int framesPassed = 0;

		//void updateFPS(sf::Time elapsedTime);
};

