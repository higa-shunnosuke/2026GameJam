#include "Player.h"

#include "../../System/InputManager.h"
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
	m_staminaMax = 100;
	m_stamina = m_staminaMax;
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
	
	// 減速
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

	// 加速
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

	// テスト用　座標の最大値、最小値、プレイヤーの半径を決めておく
	Vector2D Min = {};
	Vector2D Max = Vector2D(1280, 720);
	float radius = 10;

	// 座標が最大値、最小値を越さないようにする
	if (m_location.x + m_moveSpeed.x - radius < Min.x)
	{
		m_moveSpeed.x = Min.x - (m_location.x - radius);
	}
	if (m_location.x + m_moveSpeed.x + radius > Max.x)
	{
		m_moveSpeed.x = Max.x - (m_location.x + radius);
	}
	if (m_location.y + m_moveSpeed.y - radius < Min.y)
	{
		m_moveSpeed.y = Min.y - (m_location.y - radius);
	}
	if (m_location.y + m_moveSpeed.y + radius > Max.y)
	{
		m_moveSpeed.y = Max.y - (m_location.y + radius);
	}


	m_location += m_moveSpeed.Normalize() *  Vector2D(fabsf(m_moveSpeed.x), fabsf(m_moveSpeed.y));


	// 掘り始める処理
	if (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		m_isDiging = TRUE;
	}

	// 掘るのをやめる処理
	if (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Released)
	{
		m_isDiging = FALSE;
	}
	
	
	// スタミナ
	if (m_stamina > m_staminaMax)
	{
		m_stamina = m_staminaMax;
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

const int& Player::GetStamina() const
{
	return m_stamina;
}
