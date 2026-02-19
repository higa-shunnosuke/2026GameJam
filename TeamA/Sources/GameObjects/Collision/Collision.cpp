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
    // 2“_ŠÔ‚Ì‹——£‚Ì2æ‚ğ‹‚ß‚é
    Vector2D diff = centerA - centerB;
    float lendth = diff.SqrLength();

    // ”¼Œa‚ğ‘«‚µ‚½2æ‚ğ‹‚ß‚é
    float total_radius = (m_radius + radiusB)*(m_radius + radiusB);

    // ’·‚³‚ğ”äŠr
    return lendth < total_radius;
}
