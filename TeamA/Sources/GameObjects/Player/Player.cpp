#include "Player.h"

#include "../../Utilitys/ProjectConfig.h"
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

	m_direction = e_Direction::right;

	// 画像のずらす値
	m_offset = { 20.f, 5.f };

	// 画像読み込み
	ResourceManager& rm = ResourceManager::GetInstance();
	
	// プレイヤー
	// 待機画像読み込み
	m_idleImage = rm.GetImageResource("Assets/Sprites/Player/Idle1.PNG")[0];

	// 歩く画像読み込み
	m_walkImage[0] = rm.GetImageResource("Assets/Sprites/Player/Walk1.PNG")[0];
	m_walkImage[1] = rm.GetImageResource("Assets/Sprites/Player/Walk2.PNG")[0];

	// 上に掘る画像読み込み
	m_upImage[0] = rm.GetImageResource("Assets/Sprites/Player/Up1.PNG")[0];
	m_upImage[1] = rm.GetImageResource("Assets/Sprites/Player/Up2.PNG")[0];
	m_upImage[2] = rm.GetImageResource("Assets/Sprites/Player/Up3.PNG")[0];

	// 下に掘る画像読み込み
	m_downImage[0] = rm.GetImageResource("Assets/Sprites/Player/Down1.PNG")[0];
	m_downImage[1] = rm.GetImageResource("Assets/Sprites/Player/Down2.PNG")[0];
	m_downImage[2] = rm.GetImageResource("Assets/Sprites/Player/Down3.PNG")[0];

	// ドリル
	// ドリル画像読み込み
	m_drillImage[0] = rm.GetImageResource("Assets/Sprites/Drill/Drill1.PNG")[0];
	m_drillImage[1] = rm.GetImageResource("Assets/Sprites/Drill/Drill2.PNG")[0];
	m_drillImage[2] = rm.GetImageResource("Assets/Sprites/Drill/Drill3.PNG")[0];

	// 上に掘る画像読み込み
	m_drillUpImage[0] = rm.GetImageResource("Assets/Sprites/Drill/Up1.PNG")[0];
	m_drillUpImage[1] = rm.GetImageResource("Assets/Sprites/Drill/Up2.PNG")[0];
	m_drillUpImage[2] = rm.GetImageResource("Assets/Sprites/Drill/Up3.PNG")[0];

	// エフェクト
	// エフェクト画像読み込み
	m_effectImage[0] = rm.GetImageResource("Assets/Sprites/Effect/Effect1.PNG")[0];
	m_effectImage[1] = rm.GetImageResource("Assets/Sprites/Effect/Effect2.PNG")[0];
	m_effectImage[2] = rm.GetImageResource("Assets/Sprites/Effect/Effect3.PNG")[0];
}

void Player::Update()
{

	m_walkAnimTime += 0.01f;
	m_drillAnimTime += 0.01f;
	m_effectAnimTime += 0.01f;
	if (m_invincibleTime >= 0.0f)
	{
		m_invincibleTime -= 0.01f;
	}

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
	float deceleration = 0.005f;

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
	float maxSpeed = 0.5f;
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

	// 座標の最大値、最小値と、プレイヤーの半径
	Vector2D Min = { 0.0f,0.0f };
	Vector2D Max = { D_STAGE_WIDTH, D_STAGE_HEIGHT };
	float radius = 40;

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

	// 向きを変える処理
	if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Hold)
	{
		if (input.GetKeyState(KEY_INPUT_UP) == eInputState::None &&
			input.GetKeyState(KEY_INPUT_DOWN) == eInputState::None)
		{
			m_direction = e_Direction::left;
		}
	}
	if (input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Hold)
	{
		if (input.GetKeyState(KEY_INPUT_UP) == eInputState::None &&
			input.GetKeyState(KEY_INPUT_DOWN) == eInputState::None)
		{
			m_direction = e_Direction::right;
		}
	}
	if (input.GetKeyState(KEY_INPUT_UP) == eInputState::Hold)
	{
		if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::None &&
			input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::None)
		{
			m_direction = e_Direction::up;
		}
	}
	if (input.GetKeyState(KEY_INPUT_DOWN) == eInputState::Hold)
	{
		if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::None &&
			input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::None)
		{
			m_direction = e_Direction::down;
		}
	}

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

}

void Player::Draw() const
{
	// 座標を見やすく、int型に
	int x = (int)m_location.x;
	int y = (int)m_location.y;

	// モグラ表示
	switch (m_direction)
	{
	case e_Direction::up:

		y -= 25;

		// モグラ表示
		if (m_walkingFlag || m_digingFlag)
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_upImage[m_walkAnimCount % 3], TRUE);
		}
		else
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_upImage[0], TRUE);
		}
		// ドリル表示
		if (m_digingFlag)
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_drillUpImage[m_drillAnimCount % 3], TRUE);
		}
		else
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_drillUpImage[0], TRUE);
		}

		// エフェクト表示
		if (m_digingFlag)
		{
			x -= 5;
			
			DrawRotaGraph(x - 5, y, 0.1, 0.65 * 3.14, m_effectImage[m_effectAnimCount % 3], TRUE);
		}

		break;
	case e_Direction::down:

		y += 10;

		// モグラ表示
		if (m_walkingFlag || m_digingFlag)
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_downImage[m_walkAnimCount % 3], TRUE);
		}
		else
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_downImage[0], TRUE);
		}

		// エフェクト表示
		if (m_digingFlag)
		{
			x += 8;
			y -= 10;

			DrawRotaGraph(x, y, 0.1, 1.65 * 3.14, m_effectImage[m_effectAnimCount % 3], TRUE);
		}
		
		break;
	case e_Direction::left:
	case e_Direction::right:

		x += (int)m_offset.x;
		y += (int)m_offset.y;

		// モグラ表示
		if (m_walkingFlag || m_digingFlag)
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_walkImage[m_walkAnimCount % 2], TRUE, m_flipFlag);
		}
		else
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_idleImage, TRUE, m_flipFlag);
		}

		// ドリル表示
		if (m_digingFlag)
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_drillImage[m_drillAnimCount % 3], TRUE, m_flipFlag);
		}
		else
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_drillImage[0], TRUE, m_flipFlag);
		}

		// エフェクト表示
		if (m_digingFlag)
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_effectImage[m_effectAnimCount % 3], TRUE, m_flipFlag);
		}

		break;
	}

	// 中心地
	//DrawCircle((int)m_location.x, (int)m_location.y, 2, 0xFFFF00, TRUE);
}

void Player::Finalize()
{

}

void Player::OnHitCollision(ObjectBase& other)
{
	switch (other.GetCollision().GetObjectType())
	{
	case e_ObjectType::potato:

		StaminaManager(20);

		break;
	case e_ObjectType::poisonpoteto:

		StaminaManager(-30);

		break;
	case e_ObjectType::rainbowpoteto:

		m_invincibleTime = 10.0f;

		break;
	case e_ObjectType::jewel:
		break;
	}
}

void Player::StaminaManager(int value)
{
	// 無敵時間中は
	if (m_invincibleTime > 0.0f)
	{
		// スタミナが減らない
		if (value < 0)
		{
			return;
		}
	}
	m_stamina += value;

	// スタミナ
	if (m_stamina > m_staminaMax)
	{
		m_stamina = m_staminaMax;
	}
}

const int& Player::GetStamina() const
{
	return m_stamina;
}

const int& Player::GetStaminaMax() const
{
	return m_staminaMax;
}
