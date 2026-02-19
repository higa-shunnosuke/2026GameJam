#pragma once
#include "../ObjectBase.h"

class Potato : public ObjectBase
{
private:

	int m_potatoImage;

public:
	Potato();
	~Potato();

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

