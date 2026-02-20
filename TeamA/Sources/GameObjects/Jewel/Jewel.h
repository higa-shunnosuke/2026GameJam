#pragma once
#include "../ObjectBase.h"

class Jewel : public ObjectBase
{
private:
	float m_animeTime;
	int m_animeCount;
	int m_emerald_image[4];

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
	void Update(float delta) override;

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

