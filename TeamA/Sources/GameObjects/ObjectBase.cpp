#include "ObjectBase.h"

ObjectBase::ObjectBase()
	:m_zLayer(0)
{
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Initialize()
{
}

void ObjectBase::Update()
{
}

void ObjectBase::Draw() const
{
}

void ObjectBase::Finalize()
{
}

void ObjectBase::OnHitCollision(ObjectBase& other)
{
}

void ObjectBase::SetLocation(const Vector2D& location)
{
	m_location = location;
}

const Vector2D& ObjectBase::GetLocation() const
{
	return m_location;
}

const int ObjectBase::GetZLayer() const
{
	return 0;
}

const Collision& ObjectBase::GetCollision() const
{
	return m_collision;
}
