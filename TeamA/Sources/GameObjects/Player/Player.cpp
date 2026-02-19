#include "Player.h"

#include <DxLib.h>

Player::Player()
{

}

Player::Player::~Player()
{

}

void Player::Initialize()
{
	m_stamina = 100;
	m_animTime = 0.0f;
	m_animCount = 0;
	m_moveSpeed = {};
}

void Player::Update()
{
	m_animTime += 0.01f;
	if (m_animTime > 1.0f)
	{
		m_animTime = 0.0f;
		m_animCount += 1;
	}
}

void Player::Draw() const
{
	DrawCircle(m_location.x, m_location.y, 10, GetColor(0, 255, 255), TRUE);
}

void Player::Finalize()
{

}

void Player::OnHitCollision(ObjectBase& other)
{

}