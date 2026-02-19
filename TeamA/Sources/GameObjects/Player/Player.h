#pragma once
#include "../ObjectBase.h"
#include "../../Utilitys/Vector2D.h"

class Player : public ObjectBase
{private:
	int m_stamina;
	int m_staminaMax;
	float m_walkAnimTime;
	int m_walkAnimCount;
	float m_drillAnimTime;
	int m_drillAnimCount;
	float m_effectAnimTime;
	int m_effectAnimCount;
	Vector2D m_moveSpeed;
	bool m_walkingFlag;
	bool m_digingFlag;
	bool m_flipFlag;
	Vector2D m_offset;
	int m_idleImage;
	int m_walkImage[2];
	int m_drillImage[3];
	int m_effectImage[3];

public:
	Player();
	~Player();

public:

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// XVˆ—
	/// </summary>
	void Update() override;

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

public:
	const int& GetStamina() const;
};

