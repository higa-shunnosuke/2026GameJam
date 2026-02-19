#include "Collision.h"

const float& Collision::GetRadius() const
{
    return m_radius;
}

const e_ObjectType Collision::GetObjectType() const
{
    return type;
}

const bool Collision::IsCircleColliding(const Vector2D& centerA, const Vector2D& centerB, const float& radiusB) const
{

}
