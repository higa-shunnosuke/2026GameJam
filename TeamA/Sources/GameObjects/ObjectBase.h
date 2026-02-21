#pragma once
#include "../Utilitys/Vector2D.h"
#include "Collision/Collision.h"

class ObjectBase
{
protected:
	Vector2D m_location;
	int m_zLayer;
	Collision m_collision;

	/* ÉåÉCÉÑÅ[ */
	// 0:PotatoPlant
	// 2:MapData
	// 10:Potato
	// 10:PoisonPotato
	// 10:RainbowPotato
	// 10:Rock
	// 10:Jewel
	// 12:Player

public:
	ObjectBase();
	~ObjectBase();

public:
	virtual void Initialize();
	virtual void Update(float delta);
	virtual void Draw() const;
	virtual void Finalize();

public:

	virtual void OnHitCollision(ObjectBase& other);

public:

	void SetLocation(const Vector2D& location);
	const Vector2D& GetLocation() const;

	const int GetZLayer()const;

	const Collision& GetCollision() const;

};