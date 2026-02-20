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
    Vector2D diff = centerA - centerB; //２点間の距離ベクトルを求める
    
    float sum = m_radius + radiusB; //半径の合計
    float c = diff.x + diff.y; //中心の距離

//半径の合計の２乗<=距離の２乗の合計なら衝突
    if (sum * sum <= c * c)
    {
        return true;
    }
    return false;
}
