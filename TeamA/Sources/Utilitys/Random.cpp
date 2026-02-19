#include "Random.h"

unsigned int Random::seed = 2463534242u;

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
