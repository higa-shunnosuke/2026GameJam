#pragma once
#include "../ObjectBase.h"

class Jewel : public ObjectBase
{
private:
	float m_animeTime;
	int m_animeCount;

public:
	Jewel();
	~Jewel();

public:

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// XVˆ—
	/// </summary>
	void UpDate() override;

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw() const override;

	/// <summary>
	/// I—¹ˆ—
	/// </summary>
	void Finalize() override;

public:

	/// <summary>
	/// ”»’èˆ—
	/// </summary>
	/// <param name="other"></param>
	void OnHitCollision(ObjectBase& other) override;
};

