#include "Player.h"

#include "../../System/InputManager.h"
#include "../../System/ResourceManager.h"
#include "../../Utilitys/ProjectConfig.h"
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
	// 当たり判定の設定	
	m_collision.m_radius = 50;
	m_collision.m_type = e_ObjectType::player;

	// zレイヤーを設定
	m_zLayer = 12;


	// スタミナ
	m_staminaMax = 100;
	m_stamina = m_staminaMax;

	// 速度
	m_moveSpeed = {};

	// フラグ
	m_walkingFlag = FALSE;
	m_digingFlag = FALSE;
	m_breakFlag = FALSE;
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
	m_offset = { 35.0f, 15.0f };

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

void Player::Update(float delta)
{
	// 操作を変数に当てはめる
	InputManager& input = InputManager::GetInstance();
	eInputState up = eInputState::None;
	eInputState down = eInputState::None;
	eInputState left = eInputState::None;
	eInputState right = eInputState::None;
	eInputState buttonA = eInputState::None;

	// 左操作
	if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Hold ||
		input.GetKeyState(KEY_INPUT_A)==eInputState::Hold)
	{
		left = eInputState::Hold;
	}
	else if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Pressed ||
		input.GetKeyState(KEY_INPUT_A) == eInputState::Pressed)
	{
		left = eInputState::Pressed;
	}
	else if (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Released ||
		input.GetKeyState(KEY_INPUT_A) == eInputState::Released)
	{
		left = eInputState::Released;
	}

	// 右操作
	if (input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Hold ||
		input.GetKeyState(KEY_INPUT_D) == eInputState::Hold)
	{
		right = eInputState::Hold;
	}
	else if (input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Pressed ||
		input.GetKeyState(KEY_INPUT_D) == eInputState::Pressed)
	{
		right = eInputState::Pressed;
	}
	else if (input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Released ||
		input.GetKeyState(KEY_INPUT_D) == eInputState::Released)
	{
		right = eInputState::Released;
	}

	// 上操作
	if (input.GetKeyState(KEY_INPUT_UP) == eInputState::Hold ||
		input.GetKeyState(KEY_INPUT_W) == eInputState::Hold)
	{
		up = eInputState::Hold;
	}
	else if (input.GetKeyState(KEY_INPUT_UP) == eInputState::Pressed ||
		input.GetKeyState(KEY_INPUT_W) == eInputState::Pressed)
	{
		up = eInputState::Pressed;
	}
	else if (input.GetKeyState(KEY_INPUT_UP) == eInputState::Released ||
		input.GetKeyState(KEY_INPUT_W) == eInputState::Released)
	{
		up = eInputState::Released;
	}

	// 下操作
	if (input.GetKeyState(KEY_INPUT_DOWN) == eInputState::Hold ||
		input.GetKeyState(KEY_INPUT_S) == eInputState::Hold)
	{
		down = eInputState::Hold;
	}
	else if (input.GetKeyState(KEY_INPUT_DOWN) == eInputState::Pressed ||
		input.GetKeyState(KEY_INPUT_S) == eInputState::Pressed)
	{
		down = eInputState::Pressed;
	}
	else if (input.GetKeyState(KEY_INPUT_DOWN) == eInputState::Released ||
		input.GetKeyState(KEY_INPUT_S) == eInputState::Released)
	{
		down = eInputState::Released;
	}

	// 掘る操作
	if (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Hold ||
		input.GetKeyState(KEY_INPUT_F) == eInputState::Hold)
	{
		buttonA = eInputState::Hold;
	}
	else if (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed ||
		input.GetKeyState(KEY_INPUT_F) == eInputState::Pressed)
	{
		buttonA = eInputState::Pressed;
	}
	else if (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Released ||
		input.GetKeyState(KEY_INPUT_F) == eInputState::Released)
	{
		buttonA = eInputState::Released;
	}

	// アニメーション時間の加算減算
	// 歩くアニメーション
	m_walkAnimTime += 0.01f;
	if (m_walkAnimTime > 0.2f)
	{
		m_walkAnimTime = 0.0f;
		m_walkAnimCount += 1;
	}

	// ドリルのアニメーション
	if (m_drillAnimCount <= 4)
	{
		m_drillAnimTime += 0.01f;
		if (m_drillAnimTime > 0.1f)
		{
			m_drillAnimTime = 0.0f;
			m_drillAnimCount += 1;
		}
	}
	else
	{
		// 掘るのをやめる処理
		m_digingFlag = FALSE;
	}

	// エフェクトのアニメーション
	if (m_effectAnimCount <= 4)
	{
		m_effectAnimTime += 0.01f;
		if (m_effectAnimTime > 0.1f)
		{
			m_effectAnimTime = 0.0f;
			m_effectAnimCount += 1;
		}
	}
	else
	{
		// 土を壊し終わる処理
		m_breakFlag = FALSE;
	}

	// 無敵の時間
	if (m_invincibleTime >= 0.0f)
	{
		m_invincibleTime -= 0.01f;
	}

	// 加速度・減速度の設定
	float deceleration = 0.1f;	// 減速度
	float maxSpeed = 2.0f;			// 速度の最大
	float acceleration = 0.2f;		// 加速度

	// 減速
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

	// 掘っていない時にのみ、移動・方向転換処理を受け付ける
	if (!m_digingFlag)
	{
		// 歩きの加速
		if (left == eInputState::Hold && m_moveSpeed.x > -maxSpeed)
		{
			m_moveSpeed.x -= acceleration;
		}
		if (right == eInputState::Hold && m_moveSpeed.x < maxSpeed)
		{
			m_moveSpeed.x += acceleration;
		}
		if (up == eInputState::Hold && m_moveSpeed.y > -maxSpeed)
		{
			m_moveSpeed.y -= acceleration;
		}
		if (down == eInputState::Hold && m_moveSpeed.y < maxSpeed)
		{
			m_moveSpeed.y += acceleration;
		}

		// 歩き始める処理
		if (left == eInputState::Pressed || right == eInputState::Pressed ||
			up == eInputState::Pressed || down == eInputState::Pressed)
		{
			m_walkingFlag = TRUE;
		}
		else
		{
			// 歩くのをやめる処理
			if (left == eInputState::None && right == eInputState::None &&
				up == eInputState::None && down == eInputState::None)
			{
				m_walkingFlag = FALSE;
			}
		}

		// 向きを変える処理
		// 左入力があるとき
		if (left == eInputState::Hold)
		{
			// 上下右入力がないなら
			if (right == eInputState::None &&
				up == eInputState::None && down == eInputState::None)
			{
				// 左に向ける
				m_direction = e_Direction::left;

				// 左右反転処理
				m_flipFlag = FALSE;
				if (m_offset.x > 0)
				{
					m_offset.x *= -1;
				}
			}
		}
		// 右入力があるとき
		if (right == eInputState::Hold)
		{
			// 上下左入力がないなら
			if (left == eInputState::None &&
				up == eInputState::None && down == eInputState::None)
			{
				// 右に向ける
				m_direction = e_Direction::right;

				// 左右反転処理
				m_flipFlag = TRUE;
				if (m_offset.x < 0)
				{
					m_offset.x *= -1;
				}
			}
		}
		// 上入力があるとき
		if (up == eInputState::Hold)
		{
			// 下左右入力がないなら
			if (left == eInputState::None && right == eInputState::None &&
				down == eInputState::None)
			{
				// 上に向ける
				m_direction = e_Direction::up;
			}
		}
		// 下入力があるとき
		if (down == eInputState::Hold)
		{
			// 上左右入力がないなら
			if (left == eInputState::None && right == eInputState::None &&
				up == eInputState::None)
			{
				// 下に向ける
				m_direction = e_Direction::down;
			}
		}

		// 移動・方向転換処理の最後
	}
	// 掘り始める処理
	if (buttonA == eInputState::Pressed)
	{
		m_digingFlag = TRUE;
		m_drillAnimCount = 0;

		// 土を壊す処理
		if (m_map->DestroySoil(m_location, m_direction))
		{
			m_breakFlag = TRUE;
			m_effectAnimCount = 0;
		}
	}

	// 掘るときに向いている方向に移動する
	if (m_digingFlag)
	{
		// 歩きの加速
		switch (m_direction)
		{
		case(e_Direction::left):

			if (m_moveSpeed.x > -maxSpeed)
			{
				m_moveSpeed.x -= acceleration;
			}

			break;
		case(e_Direction::right):

			if (m_moveSpeed.x < maxSpeed)
			{
				m_moveSpeed.x += acceleration;
			}

			break;
		case(e_Direction::up):

			if (m_moveSpeed.y > -maxSpeed)
			{
				m_moveSpeed.y -= acceleration;
			}

			break;
		case(e_Direction::down):

			if (m_moveSpeed.y < maxSpeed)
			{
				m_moveSpeed.y += acceleration;
			}

			break;
		}
	}

	// 座標の最大値、最小値と、プレイヤーの半径
	Vector2D Min = { 0.0f,0.0f };
	Vector2D Max = { D_STAGE_WIDTH, D_STAGE_HEIGHT };

	// 座標が最大値、最小値を越さないようにする
	if (m_location.x + m_moveSpeed.x - m_collision.m_radius < Min.x)
	{
		m_moveSpeed.x = Min.x - (m_location.x - m_collision.m_radius);
	}
	if (m_location.x + m_moveSpeed.x + m_collision.m_radius > Max.x)
	{
		m_moveSpeed.x = Max.x - (m_location.x + m_collision.m_radius);
	}
	if (m_location.y + m_moveSpeed.y - m_collision.m_radius < Min.y)
	{
		m_moveSpeed.y = Min.y - (m_location.y - m_collision.m_radius);
	}
	if (m_location.y + m_moveSpeed.y + m_collision.m_radius > Max.y)
	{
		m_moveSpeed.y = Max.y - (m_location.y + m_collision.m_radius);
	}

	// ブロックとの当たり判定
	{
		// 進行方向のタイル座標を取得
		Vector2D position;
		switch (m_direction)
		{
		case e_Direction::up:
			position = { m_location.x,m_location.y - m_collision.m_radius };
			break;
		case e_Direction::down:
			position = { m_location.x,m_location.y + m_collision.m_radius };
			break;
		case e_Direction::left:
			position = { m_location.x - m_collision.m_radius,m_location.y };
			break;
		case e_Direction::right:
			position = { m_location.x + m_collision.m_radius,m_location.y };
			break;
		}
		Vector2D nextTileLocation = m_map->GetTileLocation(position);

		// 道でなければ移動速度を削除
		if (m_map->TileType(nextTileLocation) != e_TileType::road)
		{
			m_moveSpeed = { 0.0f,0.0f };
		}
	}


	// テスト用
	if (input.GetKeyState(KEY_INPUT_U) == eInputState::Hold)
	{
		m_location.x += 1;
	}
	if (input.GetKeyState(KEY_INPUT_I) == eInputState::Hold)
	{
		m_location.x -= 1;
	}
	if (input.GetKeyState(KEY_INPUT_O) == eInputState::Hold)
	{
		m_location.y += 1;
	}
	if (input.GetKeyState(KEY_INPUT_P) == eInputState::Hold)
	{
		m_location.y -= 1;
	}

	// 座標に速度を加算
	m_location += m_moveSpeed.Normalize() * Vector2D(fabsf(m_moveSpeed.x), fabsf(m_moveSpeed.y));
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

		y += (int)m_offset.y;
		y -= 30;

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
		if (m_breakFlag)
		{
			x -= 5;
			
			DrawRotaGraph(x - 5, y, 0.1, 0.65 * 3.14, m_effectImage[m_effectAnimCount % 3], TRUE);
		}

		break;
	case e_Direction::down:

		y += (int)m_offset.y;
		y += 5;

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
		if (m_breakFlag)
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
		if (m_breakFlag)
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_effectImage[m_effectAnimCount % 3], TRUE, m_flipFlag);
		}

		break;
	}

	// 中心地
	DrawCircleAA(m_location.x,m_location.y, 1.5,30, 0x000000, TRUE);
	// 当たり判定
	DrawCircleAA(m_location.x, m_location.y, m_collision.m_radius, 30, GetColor(255, 0, 0), FALSE);
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

void Player::SetMap(MapData* mapdata)
{
	m_map = mapdata;
}
