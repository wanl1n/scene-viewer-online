#include "FPSCounter.h"
#include <iostream>
#include <string>
//#include "BaseRunner.h"

FPSCounter::FPSCounter()
{
	//sf::Font* font = new sf::Font();
	//font->openFromFile("Media/SeriesOrbit.TTF");

	//this->statsText = new sf::Text(*font);
	//this->statsText->setFont(*font);
	//this->statsText->setPosition(sf::Vector2f(BaseRunner::WINDOW_WIDTH - 150, BaseRunner::WINDOW_HEIGHT - 70));
	//this->statsText->setFillColor(sf::Color(255, 255, 255));
	////this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	//this->statsText->setOutlineThickness(4.0f);
	//this->statsText->setCharacterSize(35);
}

FPSCounter::~FPSCounter()
{
	//delete this->statsText;
}

void FPSCounter::update(float deltaTime)
{
	/*if (clock.getElapsedTime().asSeconds() > 0.5f)
	{
		this->updateFPS(deltaTime);
		clock.restart();
	}*/
}

//void FPSCounter::draw(sf::RenderWindow* targetWindow)
//{
//	//AGameObject::draw(targetWindow);
//
//	if(this->statsText != nullptr)
//		targetWindow->draw(*this->statsText);
//}

//void FPSCounter::updateFPS(sf::Time elapsedTime)
//{
//	int fps = (int)floor(1 / elapsedTime.asSeconds());
//	sf::String fpsString = "FPS: " + std::to_string(fps) + "\n";
//	this->statsText->setString(fpsString);
//}
