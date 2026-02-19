#include "Player.h"

#include "../../Systems/InputManager.h"
#include <DxLib.h>
#include <math.h>

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
	m_isDiging = FALSE;
}

void Player::Update()
{
	m_animTime += 0.01f;
	if (m_animTime > 1.0f)
	{
		m_animTime = 0.0f;
		m_animCount += 1;
	}

	InputManager& input = InputManager::GetInstance();
	
	// Œ¸‘¬
	float deceleration = 0.002f;

	if (m_moveSpeed.x > deceleration)
	{
		m_moveSpeed.x -= deceleration;
	}
	else if (m_moveSpeed.x < -deceleration)
	{
		m_moveSpeed.x += deceleration;
	}
	else
	{
		m_moveSpeed.x = 0.0f;
	}
	if (m_moveSpeed.y > deceleration)
	{
		m_moveSpeed.y -= deceleration;
	}
	else if (m_moveSpeed.y < -deceleration)
	{
		m_moveSpeed.y += deceleration;
	}
	else
	{
		m_moveSpeed.y = 0.0f;
	}

	// ‰Á‘¬
	float maxSpeed = 0.4f;
	float acceleration = 0.05f;

	if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Hold && m_moveSpeed.x > -maxSpeed)
	{
		m_moveSpeed.x -= acceleration;
	}
	if (input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Hold && m_moveSpeed.x < maxSpeed)
	{
		m_moveSpeed.x += acceleration;
	}
	if (input.GetKeyState(KEY_INPUT_UP) == eInputState::Hold && m_moveSpeed.y > -maxSpeed)
	{
		m_moveSpeed.y -= acceleration;
	}
	if (input.GetKeyState(KEY_INPUT_DOWN) == eInputState::Hold && m_moveSpeed.y < maxSpeed)
	{
		m_moveSpeed.y += acceleration;
	}

	m_location += m_moveSpeed.Normalize() *  Vector2D(fabsf(m_moveSpeed.x), fabsf(m_moveSpeed.y));


	// Œ@‚èŽn‚ß‚éˆ—
	if (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		m_isDiging = TRUE;
	}

	// Œ@‚é‚Ì‚ð‚â‚ß‚éˆ—
	if (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Released)
	{
		m_isDiging = FALSE;
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