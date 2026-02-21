#pragma once
#include "../../Utilitys/Vector2D.h"

enum class e_ObjectType
{
	none,
	player,			// プレイヤー
	potato,			// ポテト
	poisonpoteto,	// 毒ポテト
	rainbowpoteto,	// 虹ポテト
	jewel			// 宝石
};

class Collision
{
public:
	float m_radius;
	e_ObjectType m_type;


public:
	Collision();
	~Collision();

public:

	const float& GetRadius() const;
	const e_ObjectType GetObjectType() const;

	/// <summary>
	/// 円と円の当たり判定確認
	/// </summary>
	/// <param name="this_location">自身の座標</param>
	/// <param name="other_location">相手の座標</param>
	/// <param name="ther_radius">相手の半径</param>
	/// <returns></returns>
	const bool IsCircleColliding(const Vector2D& this_location, const Vector2D& other_location, const float& other_radius) const;
};