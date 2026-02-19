#pragma once

class Random
{
private:
	static unsigned int seed;

public:

	static void SetSeed(unsigned int s);
	static unsigned int GetRand();

};