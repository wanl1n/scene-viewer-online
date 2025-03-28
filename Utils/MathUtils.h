#pragma once
#include <cmath>
#include <random>

class MathUtils
{
public:
	/*template <typename T>
	static sf::Vector2<T> interpolateTowards(sf::Vector2<T> current, sf::Vector2<T> target, float maxDistanceDelta)
	{
		sf::Vector2<T> a = target - current;
		float magnitude = a.length();
		if (magnitude <= maxDistanceDelta || magnitude == 0.f)
		{
			return target;
		}
		return current + a / magnitude * maxDistanceDelta;
	}

	template <typename T>
	static sf::Vector3<T> interpolateTowards(sf::Vector3<T> current, sf::Vector3<T> target, float maxDistanceDelta)
	{
		sf::Vector3<T> a = target - current;
		float magnitude = a.length();
		if (magnitude <= maxDistanceDelta || magnitude == 0.f)
		{
			return target;
		}
		return current + a / magnitude * maxDistanceDelta;
	}*/

	template <typename T>
	static int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	static float interpolateTowards(float current, float target, float maxDelta)
	{
		if (abs(target - current) <= maxDelta)
		{
			return target;
		}
		return current + sgn(target - current) * maxDelta;
	}

	static int randomInt(int min, int max)
	{
		// Initialize a random number generator
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(min, max);

		// Generate random number in the range [min, max]
		return distrib(gen);
	}

	static float randomFloat(float min, float max)
	{
		// Initialize a random number generator
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(min, max);

		// Generate random number in the range [min, max]
		return distrib(gen);
	}
};