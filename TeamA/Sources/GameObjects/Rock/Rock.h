#pragma once
#include "../ObjectBase.h"

class Rock : public ObjectBase
{
private:
	float m_animeTime;
	int m_animeCount;

public:
	Rock();
	~Rock();

public:

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw() const override;

public:

	/// <summary>
	/// ”»’èˆ—
	/// </summary>
	/// <param name="other"></param>
	void OnHitCollision(ObjectBase& other) override;
};

