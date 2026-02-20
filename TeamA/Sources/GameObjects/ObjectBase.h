#pragma once
#include "../Utilitys/Vector2D.h"
#include "Collision/Collision.h"

class ObjectBase
{
protected:
	Vector2D m_location;
	int m_zLayer;
	Collision m_collision;

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