#pragma once

class Random
{
private:
	static unsigned int seed;

public:
	Random();
	~Random();

	static void SetSeed(unsigned int s);
	static unsigned int GetRand();

};