#pragma once
#include "../ObjectBase.h"
#include "../../Utilitys/Vector2D.h"

class Player : public ObjectBase
{private:
	int m_stamina;
	float m_animTime;
	int m_animCount;
	Vector2D m_moveSpeed;
	bool m_isDiging;

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
};

