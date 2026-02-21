#include "Collision.h"

Collision::Collision()
    :m_type(e_ObjectType::none)
    ,m_radius(0)
{
}

Collision::~Collision()
{
}

const float& Collision::GetRadius() const
{
    return m_radius;
}

const e_ObjectType Collision::GetObjectType() const
{
    return m_type;
}

const bool Collision::IsCircleColliding(const Vector2D& centerA, const Vector2D& centerB, const float& radiusB) const
{
    Vector2D diff = centerA - centerB; //‚Q“_ŠÔ‚Ì‹——£ƒxƒNƒgƒ‹‚ğ‹‚ß‚é
    
    float sum = m_radius + radiusB; //”¼Œa‚Ì‡Œv
    float c = diff.x * diff.x + diff.y * diff.y; //2“_ŠÔ‚Ì‹——£‚Ì2æ

//”¼Œa‚Ì‡Œv‚Ì‚Qæ>=‹——£‚Ì‡Œv(2æ)‚È‚çÕ“Ë
    if (sum * sum >= c )
    {
        return true;
    }
    return false;
}
