#pragma once
#include "../Utilitys/Vector2D.h"

class ObjectBase
{
protected:
	Vector2D m_location;
	int m_zLayer;

public:
	ObjectBase();
	~ObjectBase();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Draw() const;
	virtual void Finalize();

public:

	virtual void OnHitCollision(ObjectBase& other);


public:

	void SetLocation(const Vector2D& location);
	const Vector2D& GetLocation() const;

	const int GetZLayer()const;




};