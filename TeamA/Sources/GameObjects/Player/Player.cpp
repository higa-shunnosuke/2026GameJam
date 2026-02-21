#include "Player.h"

#include "../../System/ResourceManager.h"
#include "../../Utilitys/ProjectConfig.h"
#include <DxLib.h>
#include <math.h>
#include <algorithm>

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

	// スコア
	m_score = 0;

	// スタミナ
	m_staminaMax = 100;
	m_stamina = m_staminaMax;

	// 速度
	m_moveSpeed = {};
	// 速度の最大
	m_maxSpeed = D_BOX_SIZE * 3;

	// フラグ
	m_walkingFlag = FALSE;
	m_diggingFlag = FALSE;
	m_breakFlag = FALSE;
	m_flipFlag = TRUE;

	// アニメーション
	m_walkAnimTime = 0.0f;
	m_walkAnimCount = 0;
	m_diggingAnimTime = 0.0f;
	m_diggingAnimCount = 0;

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
	// 対応入力の変数化
	ApplyInput();
	// アニメーション
	LapseAnimation(delta);
	// 操作
	PlayerOperate(delta);
}

void Player::Draw() const
{
	// 座標を見やすく、int型に
	float x = m_location.x;
	float y = m_location.y;

	// モグラ表示
	switch (m_direction)
	{
	case e_Direction::up:

		y += m_offset.y;
		y -= 30.0f;

		// モグラ表示
		if (m_walkingFlag || m_diggingFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_upImage[m_walkAnimCount % 3], TRUE);
		}
		else
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_upImage[0], TRUE);
		}
		// ドリル表示
		if (m_diggingFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_drillUpImage[m_diggingAnimCount % 3], TRUE);
		}
		else
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_drillUpImage[0], TRUE);
		}

		// エフェクト表示
		if (m_breakFlag)
		{
			x -= 5.0f;
			
			DrawRotaGraphF(x - 5, y, 0.1, 0.65 * 3.14, m_effectImage[m_diggingAnimCount % 3], TRUE);
		}

		break;
	case e_Direction::down:

		y += m_offset.y;
		y += 5.0f;

		// モグラ表示
		if (m_walkingFlag || m_diggingFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_downImage[m_walkAnimCount % 3], TRUE);
		}
		else
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_downImage[0], TRUE);
		}

		// ドリル表示
		if (m_diggingFlag)
		{
			//DrawRotaGraphF(x, y, 0.1, 0.0, m_drillDownImage[m_diggingAnimCount % 3], TRUE);
		}
		else
		{
			//DrawRotaGraphF(x, y, 0.1, 0.0, m_drillDownImage[0], TRUE);
		}

		// エフェクト表示
		if (m_breakFlag)
		{
			x += 8.0f;
			y -= 10.0f;

			DrawRotaGraphF(x, y, 0.1, 1.65 * 3.14, m_effectImage[m_diggingAnimCount % 3], TRUE);
		}
		
		break;
	case e_Direction::left:
	case e_Direction::right:

		x += m_offset.x;
		y += m_offset.y;

		// モグラ表示
		if (m_walkingFlag || m_diggingFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_walkImage[m_walkAnimCount % 2], TRUE, m_flipFlag);
		}
		else
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_idleImage, TRUE, m_flipFlag);
		}

		// ドリル表示
		if (m_diggingFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_drillImage[m_diggingAnimCount % 3], TRUE, m_flipFlag);
		}
		else
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_drillImage[0], TRUE, m_flipFlag);
		}

		// エフェクト表示
		if (m_breakFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_effectImage[m_diggingAnimCount % 3], TRUE, m_flipFlag);
		}

		break;
	}

	// 中心地
	DrawCircleAA(m_location.x,m_location.y, 1.5,30, 0x000000, TRUE);
	// 当たり判定
	//DrawCircleAA(m_location.x, m_location.y, m_collision.m_radius, 30, GetColor(255, 0, 0), FALSE);
}

void Player::Finalize()
{

}

void Player::OnHitCollision(ObjectBase& other)
{
	switch (other.GetCollision().m_type)
	{
	case e_ObjectType::potato:

		StaminaManager(20);

		break;
	case e_ObjectType::poisonpoteto:

		StaminaManager(-30);

		break;
	case e_ObjectType::rainbowpoteto:

		StaminaManager(20);
		m_invincibleTime = 10.0f;

		break;
	case e_ObjectType::jewel:

		ScoreManager(100);

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

void Player::ScoreManager(int value)
{
	m_score += value;

	// スコアを0未満にしない
	if (m_score < 0)
	{
		m_score = 0;
	}
}

void Player::ApplyInput()
{
	InputManager& input = InputManager::GetInstance();

	int getInput[3];
	
	getInput[0] = KEY_INPUT_UP;
	getInput[1] = KEY_INPUT_W;
	getInput[2] = XINPUT_BUTTON_DPAD_UP;
	m_up = input.ApplyOneInput(getInput, 3);

	getInput[0] = KEY_INPUT_DOWN;
	getInput[1] = KEY_INPUT_S;
	getInput[2] = XINPUT_BUTTON_DPAD_DOWN;
	m_down = input.ApplyOneInput(getInput, 3);

	getInput[0] = KEY_INPUT_LEFT;
	getInput[1] = KEY_INPUT_A;
	getInput[2] = XINPUT_BUTTON_DPAD_LEFT;
	m_left = input.ApplyOneInput(getInput, 3);

	getInput[0] = KEY_INPUT_RIGHT;
	getInput[1] = KEY_INPUT_D;
	getInput[2] = XINPUT_BUTTON_DPAD_RIGHT;
	m_right = input.ApplyOneInput(getInput, 3);

	getInput[0] = KEY_INPUT_SPACE;
	getInput[1] = XINPUT_BUTTON_A;
	getInput[2] = XINPUT_BUTTON_B;
	m_digButton = input.ApplyOneInput(getInput, 3);

	
}

void Player::LapseAnimation(float deltaSecond)
{
	// 歩くアニメーション
	m_walkAnimTime += deltaSecond;
	if (m_walkAnimTime > 0.2)
	{
		m_walkAnimTime = 0.0f;
		m_walkAnimCount += 1;
	}

	// ドリルのアニメーション
	if (m_diggingAnimCount <= 1 || m_digButton == eInputState::Hold)
	{
		m_diggingAnimTime += deltaSecond;
		if (m_diggingAnimTime > 0.1)
		{
			m_diggingAnimTime = 0.0f;
			m_diggingAnimCount += 1;
		}
	}
	else if(m_diggingFlag)
	{
		// 掘るり終わる処理
		m_diggingFlag = FALSE;
		// 土を壊し終わる処理
		m_breakFlag = FALSE;
	}

	// 無敵の時間
	if (m_invincibleTime >= 0.0f)
	{
		m_invincibleTime -= deltaSecond;
	}
}

void Player::PlayerOperate(float deltaSecond)
{
	InputManager& input = InputManager::GetInstance();

	// 加速度の設定
	float acceleration = m_maxSpeed * 4 * deltaSecond;
	// 減速度の設定
	float deceleration = m_maxSpeed * 3 * deltaSecond;

	PlayerDeceleration(deceleration);

	// 掘っていない時にのみ、移動・方向転換処理を受け付ける
	if (!m_diggingFlag)
	{
		PlayerWalkingOperation(acceleration);
		PlayerChangeDirection();

		// 移動・方向転換処理の最後
	}

	// 掘り始める処理
	if (m_digButton == eInputState::Pressed)
	{
		m_diggingFlag = TRUE;
		m_diggingAnimCount = 0;
	}
	if (m_diggingFlag)
	{
		// 土を壊す処理
		if (m_map->DestroySoil(m_location, m_direction))
		{
			m_breakFlag = TRUE;
		}
	}

	if (m_diggingFlag)
	{
		MoveInTheDiggingDirection(acceleration);
	}

	// 世界の限界
	Vector2D Min = { 0.0f,0.0f };
	Vector2D Max = { D_STAGE_WIDTH, D_STAGE_HEIGHT };

	// 移動後が世界の限界を超えていれば
	if (m_location.x + m_moveSpeed.x * deltaSecond - m_collision.m_radius < Min.x)
	{
		m_location.x = Min.x + m_collision.m_radius;
		m_moveSpeed.x = 0.0f;
	}
	if (m_location.x + m_moveSpeed.x * deltaSecond + m_collision.m_radius > Max.x)
	{
		m_location.x = Max.x - m_collision.m_radius;
		m_moveSpeed.x = 0.0f;
	}
	if (m_location.y + m_moveSpeed.y * deltaSecond - m_collision.m_radius < Min.y)
	{
		m_location.y = Min.y + m_collision.m_radius;
		m_moveSpeed.y = 0.0f;
	}
	if (m_location.y + m_moveSpeed.y * deltaSecond + m_collision.m_radius > Max.y)
	{
		m_location.y = Max.y - m_collision.m_radius;
		m_moveSpeed.y = 0.0f;
	}

	CollisionDetectionWithBlocks(deltaSecond);

	// 移動速度をフレーム単位に変換
	Vector2D deltaMoveSpeed = { m_moveSpeed.x * deltaSecond,m_moveSpeed.y * deltaSecond };
	// 座標に速度を加算
	m_location += deltaMoveSpeed.Normalize() * Vector2D(fabsf(deltaMoveSpeed.x), fabsf(deltaMoveSpeed.y));
}

void Player::PlayerDeceleration(float deceleration)
{
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
}

void Player::PlayerWalkingOperation(float acceleration)
{
	// 加速
	if (m_left == eInputState::Hold && m_moveSpeed.x > -m_maxSpeed)
	{
		m_moveSpeed.x -= acceleration;
	}
	if (m_right == eInputState::Hold && m_moveSpeed.x < m_maxSpeed)
	{
		m_moveSpeed.x += acceleration;
	}
	if (m_up == eInputState::Hold && m_moveSpeed.y > -m_maxSpeed)
	{
		m_moveSpeed.y -= acceleration;
	}
	if (m_down == eInputState::Hold && m_moveSpeed.y < m_maxSpeed)
	{
		m_moveSpeed.y += acceleration;
	}

	if (m_left == eInputState::Hold || m_right == eInputState::Hold ||
		m_up == eInputState::Hold || m_down == eInputState::Hold)
	{
		// 歩く
		m_walkingFlag = TRUE;
	}
	else
	{
		// 歩いていない
		m_walkingFlag = FALSE;
	}
}

void Player::PlayerChangeDirection()
{
	ChangeOneDirection(e_Direction::left, m_left);
	ChangeOneDirection(e_Direction::right, m_right);
	ChangeOneDirection(e_Direction::up, m_up);
	ChangeOneDirection(e_Direction::down, m_down);
}

void Player::ChangeOneDirection(e_Direction direction, eInputState inputState)
{
	// その入力があるとき
	if (inputState == eInputState::Hold)
	{
		switch (direction)
		{
		case e_Direction::up:
			// 移動が下方向
			if (m_moveSpeed.y >= 0.0f)
			{
				// 処理を終了する
				return;
			}
			// 向いている方向が下ではない
			if (m_direction != e_Direction::down)
			{
				// 左右が押されているとき
				if (m_left != eInputState::None || m_right != eInputState::None)
				{
					// 処理を終了する
					return;
				}
			}
			break;

		case e_Direction::down:
			// 移動が上方向
			if (m_moveSpeed.y <= 0.0f)
			{
				// 処理を終了する
				return;
			}
			// 向いている方向が上ではない
			if (m_direction != e_Direction::up)
			{
				// 左右が押されているとき
				if (m_left != eInputState::None || m_right != eInputState::None)
				{
					// 処理を終了する
					return;
				}
			}
			break;

		case e_Direction::left:
			// 移動が右方向
			if (m_moveSpeed.x >= 0.0f)
			{
				// 処理を終了する
				return;
			}
			// 向いている方向が右ではない
			if (m_direction != e_Direction::right)
			{
				// 上下が押されているとき
				if (m_up != eInputState::None || m_down != eInputState::None)
				{
					// 処理を終了する
					return;
				}
			}
			break;

		case e_Direction::right:
			// 移動が左方向
			if (m_moveSpeed.x <= 0.0f)
			{
				// 処理を終了する
				return;
			}
			// 向いている方向が左ではない
			if (m_direction != e_Direction::left)
			{
				// 上下が押されているとき
				if (m_up != eInputState::None || m_down != eInputState::None)
				{
					// 処理を終了する
					return;
				}
			}
			break;
		}

		// その方向に向ける
		m_direction = direction;

		switch (direction)
		{
		case e_Direction::left:
			// 左に反転
			m_flipFlag = FALSE;
			if (m_offset.x > 0.0f)
			{
				m_offset.x *= -1;
			}
			break;

		case e_Direction::right:
			// 右に反転
			m_flipFlag = TRUE;
			if (m_offset.x < 0.0f)
			{
				m_offset.x *= -1;
			}
			break;
		}
	}
}

void Player::MoveInTheDiggingDirection(float acceleration)
{
	// 歩きの加速
	switch (m_direction)
	{
	case(e_Direction::left):

		if (m_moveSpeed.x > -m_maxSpeed)
		{
			m_moveSpeed.x -= acceleration;
		}

		break;
	case(e_Direction::right):

		if (m_moveSpeed.x < m_maxSpeed)
		{
			m_moveSpeed.x += acceleration;
		}

		break;
	case(e_Direction::up):

		if (m_moveSpeed.y > -m_maxSpeed)
		{
			m_moveSpeed.y -= acceleration;
		}

		break;
	case(e_Direction::down):

		if (m_moveSpeed.y < m_maxSpeed)
		{
			m_moveSpeed.y += acceleration;
		}

		break;
	}
}

void Player::CollisionDetectionWithBlocks(float deltaSecond)
{
	// 上のブロック
	if (PlayerPushingByBlocks({ m_location.x, m_location.y - D_BOX_SIZE / 2 }, deltaSecond))
	{
		// 衝突したら、Y方向の加速をリセット
		m_moveSpeed.y = 0.0f;
	}
	// 下のブロック
	if (PlayerPushingByBlocks({ m_location.x, m_location.y + D_BOX_SIZE / 2 }, deltaSecond))
	{
		// 衝突したら、Y方向の加速をリセット
		m_moveSpeed.y = 0.0f;
	}
	// 左のブロック
	if (PlayerPushingByBlocks({ m_location.x - D_BOX_SIZE / 2, m_location.y }, deltaSecond))
	{
		// 衝突したら、X方向の加速をリセット
		m_moveSpeed.x = 0.0f;
	}
	// 右のブロック
	if (PlayerPushingByBlocks({ m_location.x + D_BOX_SIZE / 2, m_location.y }, deltaSecond))
	{
		// 衝突したら、X方向の加速をリセット
		m_moveSpeed.x = 0.0f;
	}
	// 左上のブロック
	PlayerPushingByBlocks({ m_location.x - D_BOX_SIZE, m_location.y - D_BOX_SIZE }, deltaSecond);
	// 右上のブロック
	PlayerPushingByBlocks({ m_location.x + D_BOX_SIZE, m_location.y - D_BOX_SIZE }, deltaSecond);
	// 左下のブロック
	PlayerPushingByBlocks({ m_location.x - D_BOX_SIZE, m_location.y + D_BOX_SIZE }, deltaSecond);
	// 右下のブロック
	PlayerPushingByBlocks({ m_location.x + D_BOX_SIZE, m_location.y + D_BOX_SIZE }, deltaSecond);
}

bool Player::PlayerPushingByBlocks(Vector2D position, float deltaSecond)
{
	// ブロックの膨らみ radius
	float blockBulge = 12.0f;

	// 移動速度をフレーム単位に変換
	Vector2D deltaMoveSpeed = { m_moveSpeed.x * deltaSecond,m_moveSpeed.y * deltaSecond };
	// 移動後の位置を設定
	Vector2D locationAfterMove = m_location + deltaMoveSpeed.Normalize() * Vector2D(fabsf(deltaMoveSpeed.x), fabsf(deltaMoveSpeed.y));

	// タイルの左上座標を取得
	Vector2D TileLocation = m_map->GetTileLocation(position) - Vector2D{ D_BOX_SIZE / 2,D_BOX_SIZE / 2 };

	// 道でなければめり込みを判定
	if (m_map->TileType(TileLocation) != e_TileType::road)
	{
		// 最近接点
		float closestX = std::clamp(locationAfterMove.x, TileLocation.x, TileLocation.x + D_BOX_SIZE);
		float closestY = std::clamp(locationAfterMove.y, TileLocation.y, TileLocation.y + D_BOX_SIZE);

		// 差分
		Vector2D diff = { locationAfterMove.x - closestX,locationAfterMove.y - closestY };

		// 距離
		float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

		// 半径
		float radius = std::sqrt(m_collision.m_radius * m_collision.m_radius) + blockBulge;

		// めり込み判定
		if (distance < radius)
		{
			// 現在の位置との差分と距離を取得
			closestX = std::clamp(m_location.x, TileLocation.x, TileLocation.x + D_BOX_SIZE);
			closestY = std::clamp(m_location.y, TileLocation.y, TileLocation.y + D_BOX_SIZE);
			diff = { m_location.x - closestX,m_location.y - closestY };
			distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

			// めり込み
			float overlap = radius - distance;

			// 押し出し
			m_location.x += (diff.x / distance) * overlap;
			m_location.y += (diff.y / distance) * overlap;

			return TRUE;
		}

	}

	return FALSE;
}

const int& Player::GetStamina() const
{
	return m_stamina;
}

const int& Player::GetScore() const
{
	return m_score;
}

void Player::SetMap(MapData* mapdata)
{
	m_map = mapdata;
}
