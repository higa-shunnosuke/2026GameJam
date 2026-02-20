#pragma once

class Random
{
private:
	static unsigned int seed;

public:

	static void SetSeed();
	static unsigned int GetRand();

};