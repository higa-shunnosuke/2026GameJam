#include "Random.h"

#include <chrono>
#include <ctime>

unsigned int Random::seed = 2463534242u;

Random::Random()
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
}

Random::~Random()
{
}

void Random::SetSeed(unsigned int s)
{
	seed = s ? s : 2463534242u;
}

unsigned int Random::GetRand()
{
	unsigned int x = seed;

	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	seed = x;
	return x * 268582165u;
}
