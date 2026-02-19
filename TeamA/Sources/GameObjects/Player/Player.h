#pragma once
#include "../ObjectBase.h"
#include "../../Utilitys/Vector2D.h"

class Player : public ObjectBase
{private:
	int m_stamina;
	float m_animTime;
	int m_animCount;
	Vector2D m_moveSpeed;

public:
	Player();
	~Player();

public:
	void Initialize() override;
	void UpDate() override;
	void Draw() const override;
	void Finalize() override;
};

