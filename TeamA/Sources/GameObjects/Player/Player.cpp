#include "Player.h"

#include "../../System/InputManager.h"
#include "../../System/ResourceManager.h"
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
	// スタミナ
	m_staminaMax = 100;
	m_stamina = m_staminaMax;

	// 速度
	m_moveSpeed = {};

	// フラグ
	m_walkingFlag = FALSE;
	m_digingFlag = FALSE;
	m_flipFlag = TRUE;

	// アニメーション
	m_walkAnimTime = 0.0f;
	m_walkAnimCount = 0;
	m_drillAnimTime = 0.0f;
	m_drillAnimCount = 0;
	m_effectAnimTime = 0.0f;
	m_effectAnimCount = 0;

	// 画像のずらす値
	m_offset = { 20.f, 5.f };

	// 画像読み込み
	ResourceManager& rm = ResourceManager::GetInstance();
	// 待機画像読み込み
	m_idleImage = rm.GetImageResource("Assets/Sprites/Characters/Player/Idle/1.PNG")[0];

	// 歩く画像読み込み
	m_walkImage[0] = rm.GetImageResource("Assets/Sprites/Characters/Player/Walk/1.PNG")[0];
	m_walkImage[1] = rm.GetImageResource("Assets/Sprites/Characters/Player/Walk/2.PNG")[0];

	// ドリル画像読み込み
	m_drillImage[0] = rm.GetImageResource("Assets/Sprites/Characters/Player/Drill/1.PNG")[0];
	m_drillImage[1] = rm.GetImageResource("Assets/Sprites/Characters/Player/Drill/2.PNG")[0];
	m_drillImage[2] = rm.GetImageResource("Assets/Sprites/Characters/Player/Drill/3.PNG")[0];

	// エフェクト画像読み込み
	m_effectImage[0] = rm.GetImageResource("Assets/Sprites/Characters/Player/Effect/1.PNG")[0];
	m_effectImage[1] = rm.GetImageResource("Assets/Sprites/Characters/Player/Effect/2.PNG")[0];
	m_effectImage[2] = rm.GetImageResource("Assets/Sprites/Characters/Player/Effect/3.PNG")[0];
}

void Player::Update()
{

	m_walkAnimTime += 0.01f;
	m_drillAnimTime += 0.01f;
	m_effectAnimTime += 0.01f;
	if (m_walkAnimTime > 1.0f)
	{
		m_walkAnimTime = 0.0f;
		m_walkAnimCount += 1;
	}
	if (m_drillAnimTime > 0.5f)
	{
		m_drillAnimTime = 0.0f;
		m_drillAnimCount += 1;
	}
	if (m_effectAnimTime > 0.5f)
	{
		m_effectAnimTime = 0.0f;
		m_effectAnimCount += 1;
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
	Vector2D Max = { 1280, 720 };
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

	// 歩き始める処理
	if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Pressed ||
		input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Pressed ||
		input.GetKeyState(KEY_INPUT_UP) == eInputState::Pressed ||
		input.GetKeyState(KEY_INPUT_DOWN) == eInputState::Pressed)
	{
		m_walkingFlag = TRUE;
	}
	else
	{
		// 歩くのをやめる処理
		if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::None &&
			input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::None &&
			input.GetKeyState(KEY_INPUT_UP) == eInputState::None &&
			input.GetKeyState(KEY_INPUT_DOWN) == eInputState::None)
		{
			m_walkingFlag = FALSE;
		}
	}


	// 掘り始める処理
	if (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		m_digingFlag = TRUE;
	}
	else
	{
		// 掘るのをやめる処理
		if (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Released)
		{
			m_digingFlag = FALSE;
		}
	}
	
	// 振り向き処理
	if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Hold)
	{
		m_flipFlag = FALSE;
		m_offset = { -35.f, 5.f };

	}
	if (input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Hold)
	{
		m_flipFlag = TRUE;
		m_offset = { 35.f, 5.f };
	}
	
	// スタミナ
	if (m_stamina > m_staminaMax)
	{
		m_stamina = m_staminaMax;
	}

}

void Player::Draw() const
{
	// モグラ表示
	if (m_walkingFlag)
	{
		DrawRotaGraph(m_location.x + m_offset.x, m_location.y + m_offset.y, 0.1, 0.0, m_walkImage[m_walkAnimCount % 2], TRUE, m_flipFlag);
	}
	else
	{
		DrawRotaGraph(m_location.x + m_offset.x, m_location.y + m_offset.y, 0.1, 0.0, m_idleImage, TRUE, m_flipFlag);
	}

	// ドリル表示
	if (m_digingFlag)
	{
		DrawRotaGraph(m_location.x + m_offset.x, m_location.y + m_offset.y, 0.1, 0.0, m_drillImage[m_drillAnimCount % 3], TRUE, m_flipFlag);
	}
	else
	{
		DrawRotaGraph(m_location.x + m_offset.x, m_location.y + m_offset.y, 0.1, 0.0, m_drillImage[0], TRUE, m_flipFlag);
	}

	// エフェクト表示
	if (m_digingFlag)
	{
		DrawRotaGraph(m_location.x + m_offset.x, m_location.y + m_offset.y, 0.1, 0.0, m_effectImage[m_effectAnimCount % 3], TRUE, m_flipFlag);
	}

	// 中心地
	DrawCircle(m_location.x, m_location.y, 2, 0xFFFF00, TRUE);
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
