#pragma once
#include "Potato.h"

class PoisonPotato : public Potato
{
private:
	int m_poisonpotatoImage;

public:
	PoisonPotato();
	~PoisonPotato();

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