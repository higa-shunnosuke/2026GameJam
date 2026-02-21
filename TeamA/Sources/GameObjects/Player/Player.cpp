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


	// スタミナ
	m_staminaMax = 100;
	m_stamina = m_staminaMax;

	// 速度
	m_moveSpeed = {};
	// 速度の最大
	m_maxSpeed = 2.0f;

	// フラグ
	m_walkingFlag = FALSE;
	m_diggingFlag = FALSE;
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
	// 対応入力
	ApplyAllInput();

	LapseAnimation();
	
	PlayerMove();
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
		if (m_walkingFlag || m_diggingFlag)
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_upImage[m_walkAnimCount % 3], TRUE);
		}
		else
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_upImage[0], TRUE);
		}
		// ドリル表示
		if (m_diggingFlag)
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
		if (m_walkingFlag || m_diggingFlag)
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
		if (m_walkingFlag || m_diggingFlag)
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_walkImage[m_walkAnimCount % 2], TRUE, m_flipFlag);
		}
		else
		{
			DrawRotaGraph(x, y, 0.1, 0.0, m_idleImage, TRUE, m_flipFlag);
		}

		// ドリル表示
		if (m_diggingFlag)
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
	switch (other.GetCollision().m_type)
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

void Player::ApplyAllInput()
{
	InputManager& input = InputManager::GetInstance();

	int getInput[2];
	
	getInput[0] = KEY_INPUT_UP;
	getInput[1] = KEY_INPUT_W;
	ApplyOneInput(m_up, getInput, 2);

	getInput[0] = KEY_INPUT_DOWN;
	getInput[1] = KEY_INPUT_S;
	ApplyOneInput(m_down, getInput, 2);

	getInput[0] = KEY_INPUT_LEFT;
	getInput[1] = KEY_INPUT_A;
	ApplyOneInput(m_left, getInput, 2);

	getInput[0] = KEY_INPUT_RIGHT;
	getInput[1] = KEY_INPUT_D;
	ApplyOneInput(m_right, getInput, 2);

	getInput[0] = KEY_INPUT_SPACE;
	getInput[1] = KEY_INPUT_F;
	ApplyOneInput(m_buttonA, getInput, 2);

}

void Player::ApplyOneInput(eInputState& variable, int getInput[], int getInputSize)
{
	InputManager& input = InputManager::GetInstance();

	for (int i = 0;i < getInputSize;i++)
	{
		// もし、対応入力のうち、どれか一つでもHoldなら
		if (input.GetKeyState(getInput[i]) == eInputState::Hold)
		{
			// 変数にHoldを当てはめる
			variable = eInputState::Hold;
			return;
		}
	}

	for (int i = 0;i < getInputSize;i++)
	{
		// もし、対応入力のうち、どれか一つでもPressedなら
		if (input.GetKeyState(getInput[i]) == eInputState::Pressed)
		{
			// 前フレームで別の対応ボタンが押されているなら
			for (int i = 0;i < getInputSize;i++)
			{
				if (input.GetKeyState(getInput[i]) == eInputState::Released)
				{
					variable = eInputState::Hold;
					return;
				}
			}
			variable = eInputState::Pressed;
			return;
		}
	}

	for (int i = 0;i < getInputSize;i++)
	{
		// もし、対応入力のうち、どれか一つでもReleasedなら
		if (input.GetKeyState(getInput[i]) == eInputState::Released)
		{
			variable = eInputState::Released;
			return;
		}
	}

	for (int i = 0;i < getInputSize;i++)
	{
		// 変数にNoneを当てはめる
		variable = eInputState::None;
	}
}

void Player::LapseAnimation()
{
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
		m_diggingFlag = FALSE;
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
}

void Player::PlayerMove()
{
	InputManager& input = InputManager::GetInstance();

	// 加速度の設定
	float acceleration = 0.2f;
	// 減速度の設定
	float deceleration = 0.1f;

	PlayerDeceleration(deceleration);

	// 掘っていない時にのみ、移動・方向転換処理を受け付ける
	if (!m_diggingFlag)
	{
		PlayerWalkingOperation(acceleration);
		PlayerChangeDirection();

		// 移動・方向転換処理の最後
	}

	// 掘り始める処理
	if (m_buttonA == eInputState::Pressed)
	{
		m_diggingFlag = TRUE;
		m_drillAnimCount = 0;

		// 土を壊す処理
		if (m_map->DestroySoil(m_location, m_direction))
		{
			m_breakFlag = TRUE;
			m_effectAnimCount = 0.0f;
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
	if (m_location.x + m_moveSpeed.x - m_collision.m_radius < Min.x)
	{
		m_moveSpeed.x = Min.x - (m_location.x - m_collision.m_radius);
		m_moveSpeed.x += deceleration;
	}
	if (m_location.x + m_moveSpeed.x + m_collision.m_radius > Max.x)
	{
		m_moveSpeed.x = Max.x - (m_location.x + m_collision.m_radius);
		m_moveSpeed.x = 0.0f;
	}
	if (m_location.y + m_moveSpeed.y - m_collision.m_radius < Min.y)
	{
		m_moveSpeed.y = Min.y - (m_location.y - m_collision.m_radius);
		m_moveSpeed.y -= deceleration;
	}
	if (m_location.y + m_moveSpeed.y + m_collision.m_radius > Max.y)
	{
		m_moveSpeed.y = Max.y - (m_location.y + m_collision.m_radius);
		m_moveSpeed.y += deceleration;
	}

	CollisionDetectionWithBlocks();

	// 座標に速度を加算
	m_location += m_moveSpeed.Normalize() * Vector2D(fabsf(m_moveSpeed.x), fabsf(m_moveSpeed.y));
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

	// 歩き始める処理
	if (m_left == eInputState::Pressed || m_right == eInputState::Pressed ||
		m_up == eInputState::Pressed || m_down == eInputState::Pressed)
	{
		m_walkingFlag = TRUE;
	}
	else
	{
		// 歩くのをやめる処理
		if (m_left == eInputState::None && m_right == eInputState::None &&
			m_up == eInputState::None && m_down == eInputState::None)
		{
			m_walkingFlag = FALSE;
		}
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
		// そのキーが左ではないかつ、左が押されているとき
		if (e_Direction::left != direction && m_left != eInputState::None)
		{
			// 処理を終了する
			return;
		}
		// そのキーが右ではないかつ、右が押されているとき
		if (e_Direction::right != direction && m_right != eInputState::None)
		{
			// 処理を終了する
			return;
		}
		// そのキーが上ではないかつ、上が押されているとき
		if (e_Direction::up != direction && m_up != eInputState::None)
		{
			// 処理を終了する
			return;
		}
		// そのキーが下ではないかつ、下が押されているとき
		if (e_Direction::down != direction && m_down != eInputState::None)
		{
			// 処理を終了する
			return;
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

void Player::CollisionDetectionWithBlocks()
{
	if (m_direction != e_Direction::down)
	{
		// 上のブロック
		if (PlayerPushingByBlocks({ m_location.x, m_location.y - D_BOX_SIZE / 2 }))
		{
			// 衝突したら、Y方向の加速をリセット
			m_moveSpeed.y = 0.0f;
		}
	}
	if (m_direction != e_Direction::up)
	{
		// 下のブロック

		if (PlayerPushingByBlocks({ m_location.x, m_location.y + D_BOX_SIZE / 2 }))
		{
			// 衝突したら、Y方向の加速をリセット
			m_moveSpeed.y = 0.0f;
		}
	}
	if (m_direction != e_Direction::right)
	{
		// 左のブロック
		if (PlayerPushingByBlocks({ m_location.x - D_BOX_SIZE / 2, m_location.y }))
		{
			// 衝突したら、X方向の加速をリセット
			m_moveSpeed.x = 0.0f;
		}
	}
	if (m_direction != e_Direction::left)
	{
		// 右のブロック
		if (PlayerPushingByBlocks({ m_location.x + D_BOX_SIZE / 2, m_location.y }))
		{
			// 衝突したら、X方向の加速をリセット
			m_moveSpeed.x = 0.0f;
		}
	}
	if (m_direction != e_Direction::down && m_direction != e_Direction::right)
	{
		// 左上のブロック
		PlayerPushingByBlocks({ m_location.x - D_BOX_SIZE / 2, m_location.y - D_BOX_SIZE / 2 });
	}
	if (m_direction != e_Direction::down && m_direction != e_Direction::left)
	{
		// 右上のブロック
		PlayerPushingByBlocks({ m_location.x + D_BOX_SIZE / 2, m_location.y - D_BOX_SIZE / 2 });
	}
	if (m_direction != e_Direction::up && m_direction != e_Direction::right)
	{
		// 左下のブロック
		PlayerPushingByBlocks({ m_location.x - D_BOX_SIZE / 2, m_location.y + D_BOX_SIZE / 2 });
	}
	if (m_direction != e_Direction::up && m_direction != e_Direction::left)
	{
		// 右下のブロック
		PlayerPushingByBlocks({ m_location.x + D_BOX_SIZE / 2, m_location.y + D_BOX_SIZE / 2 });
	}
}

bool Player::PlayerPushingByBlocks(Vector2D position)
{
	// 移動後の位置を設定
	Vector2D locationAfterMove = m_location + m_moveSpeed;

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
		float radius = std::sqrt(m_collision.m_radius * m_collision.m_radius);

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

const int& Player::GetStaminaMax() const
{
	return m_staminaMax;
}

void Player::SetMap(MapData* mapdata)
{
	m_map = mapdata;
}
