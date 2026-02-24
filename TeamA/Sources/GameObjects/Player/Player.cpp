#include "Player.h"

#include "../../System/ResourceManager.h"
#include "../../Utilitys/ProjectConfig.h"
#include <DxLib.h>
#include <math.h>
#include <algorithm>

#define D_POTATO_CALORIE	(100)	// ポテトの回復量
#define D_POTATO_STOCK		(2)		// 初期の所持ポテト
#define D_DIG_COST			(-15)	// 採掘のスタミナ消費量

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

	// ポテト
	m_potatoStock = D_POTATO_STOCK;

	// 速度
	m_moveSpeed = {};
	// 速度の最大
	m_maxSpeed = D_BOX_SIZE * 3;

	// フラグ
	m_diggingFlag = false;
	m_breakFlag = false;

	// アニメーション
	m_walkAnimTime = 0.0f;
	m_walkAnimCount = 0;
	m_diggingAnimTime = 0.0f;
	m_diggingAnimCount = 0;

	// 最初の向き
	m_direction = e_Direction::right;
	m_animState = e_AnimationState::move;

	m_isStartAnimFinished = false;
	m_isEndAnimFinished = false;

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

	// 食べている画像
	m_eatImage[0] = rm.GetImageResource("Assets/Sprites/Player/Eat1.PNG")[0];
	m_eatImage[1] = rm.GetImageResource("Assets/Sprites/Player/Eat2.PNG")[0];
	m_eatImage[2] = rm.GetImageResource("Assets/Sprites/Player/Eat3.PNG")[0];

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
	// スタート時の処理
	if (!m_isStartAnimFinished)
	{
		m_location.x += 100.0f * delta;
		// 歩くアニメ
		m_walkAnimTime += delta;
		if (m_walkAnimTime > 0.2f)
		{
			m_walkAnimTime = 0.0f;
			m_walkAnimCount++;
		}
		if (m_location.x >= D_BOX_SIZE * 0.5f)
		{
			m_isStartAnimFinished = true;
		}
		return;
	}

	// 終了時の処理
	if (m_animState == e_AnimationState::dead)
	{
		// アニメが終了したら
		m_isEndAnimFinished = true;
		return;
	}

	if (m_animTimer < 0.0f)
	{
		m_animTimer = 0.0f;

		// 食事のアニメーションが終わったら
		if (m_animState == e_AnimationState::eat)
		{
			// ポテトを使用する
			StaminaManager(D_POTATO_CALORIE);
			m_potatoStock--;
		}
		m_animState = e_AnimationState::idle;
	}
	else
	{
		m_animTimer -= delta;
	}

	// 食べてる間じゃなければ
	if (m_animState != e_AnimationState::eat)
	{
		// アニメーション
		LapseAnimation(delta);
		// 移動処理
		UpdatePlayerState(delta);
	}
	else
	{
		m_eatTimer += delta;
		if (m_eatTimer > 0.3f)
		{
			m_eatCount = (++m_eatCount) % 3;
		}
	}
}

void Player::Draw() const
{
	bool flipFlag = false;
	Vector2D 	offset = { 0.0f, 15.0f };

	// 向きによって反転フラグとオフセットを変更する
	switch (m_direction)
	{
	case e_Direction::left:
		// 左に反転
		flipFlag = false;
		offset.x = -35.0f;
		break;
	case e_Direction::right:
		// 右に反転
		flipFlag = true;
		offset.x = 35.0f;
		break;
	}

	if (m_animState == e_AnimationState::eat)
	{
		float offsetx = (flipFlag) ? 35.0f : -35.0f;
		float offsety = 15.0f;

		DrawRotaGraphF(m_location.x + offsetx, m_location.y + 15.0f, 0.1f, 0.0, m_eatImage[m_eatCount], true, flipFlag);
		return;
	}

	if (offset.x == 0) offset.x= 35.0f;

	// 座標を見やすく、int型に
	float x = m_location.x;
	float y = m_location.y;

	// モグラ表示
	switch (m_direction)
	{
	case e_Direction::up:

		y += offset.y;
		y -= 30.0f;

		// モグラ表示
		if (m_animState == e_AnimationState::move || m_diggingFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_upImage[m_walkAnimCount % 3], true);
		}
		else
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_upImage[0], true);
		}
		// ドリル表示
		if (m_diggingFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_drillUpImage[m_diggingAnimCount], true);
		}
		else
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_drillUpImage[0], true);
		}

		// エフェクト表示
		if (m_breakFlag)
		{
			x -= 5.0f;
			
			DrawRotaGraphF(x - 5, y, 0.1, 0.65 * 3.14, m_effectImage[m_diggingAnimCount], true);
		}

		break;
	case e_Direction::down:

		y += offset.y;
		y += 5.0f;

		// モグラ表示
		if (m_animState == e_AnimationState::move || m_diggingFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_downImage[m_walkAnimCount % 3], true);
		}
		else
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_downImage[0], true);
		}

		// ドリル表示
		if (m_diggingFlag)
		{
			//DrawRotaGraphF(x, y, 0.1, 0.0, m_drillDownImage[m_diggingAnimCount % 3], true);
		}
		else
		{
			//DrawRotaGraphF(x, y, 0.1, 0.0, m_drillDownImage[0], true);
		}

		// エフェクト表示
		if (m_breakFlag)
		{
			x += 8.0f;
			y -= 10.0f;

			DrawRotaGraphF(x, y, 0.1, 1.65 * 3.14, m_effectImage[m_diggingAnimCount], true);
		}
		
		break;
	case e_Direction::left:
	case e_Direction::right:

		x += offset.x;
		y += offset.y;

		// モグラ表示
		if (m_animState == e_AnimationState::move || m_diggingFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_walkImage[m_walkAnimCount % 2], true, flipFlag);
		}
		else
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_idleImage, true, flipFlag);
		}

		// ドリル表示
		if (m_diggingFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_drillImage[m_diggingAnimCount], true, flipFlag);
		}
		else
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_drillImage[0], true, flipFlag);
		}

		// エフェクト表示
		if (m_breakFlag)
		{
			DrawRotaGraphF(x, y, 0.1, 0.0, m_effectImage[m_diggingAnimCount], true, flipFlag);
		}

		break;
	}

#ifdef _DEBUG
	// 中心地
	DrawCircleAA(m_location.x,m_location.y, 1.5,30, 0x000000, true);
	// 当たり判定
	DrawCircleAA(m_location.x, m_location.y, m_collision.m_radius, 30, GetColor(255, 0, 0), false);

	SetFontSize(30);
	DrawFormatStringF(m_location.x, m_location.y - 75.0f, 0xffffff, "%d", m_potatoStock);
	SetFontSize(12);

#endif
}

void Player::Finalize()
{

}

void Player::OnHitCollision(ObjectBase& other)
{
	switch (other.GetCollision().m_type)
	{
	case e_ObjectType::potato:

		// ジャガイモのストックを増やす
		m_potatoStock++;
		break;

	case e_ObjectType::poisonpoteto:

		// スタミナの減少
		StaminaManager(-30);

		break;
	case e_ObjectType::rainbowpoteto:

		// スタミナ回復
		StaminaManager(20);

		// スタミナ減少無効果時間を設定
		m_invincibleTime = 10.0f;

		break;
	case e_ObjectType::jewel:

		// スコアを加算
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

	// スタミナの上限
	if (m_stamina > m_staminaMax)
	{
		m_stamina = m_staminaMax;
	}

	// 0以下の時
	if (m_stamina <= 0)
	{
		// ポテトストックがあれば
		if (m_potatoStock > 0)
		{
			// 状態を変更
			m_animState = e_AnimationState::eat;
			m_animTimer = 1.0f;

			// ドリルと土煙のエフェクトをなくす
			m_diggingFrameTimer = 0.0f;
		}
		else
		{
			m_animState = e_AnimationState::dead;
		}
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

void Player::LapseAnimation(float deltaSecond)
{
	// 歩くアニメーション
	m_walkAnimTime += deltaSecond;
	if (m_walkAnimTime > 0.2)
	{
		m_walkAnimTime = 0.0f;
		m_walkAnimCount += 1;
	}

	// ドリル/土エフェクト
	if (m_diggingFrameTimer > 0.0f)
	{
		m_diggingAnimTime += deltaSecond;
		if (m_diggingAnimTime > 0.1f)
		{
			m_diggingAnimTime = 0.0f;
			m_diggingAnimCount = (m_diggingAnimCount + 1) % 3;
		}
	}

	// 土煙を出す時間
	m_diggingFrameTimer -= deltaSecond;
	if (m_diggingFrameTimer <= 0.0f)
	{
		// 土を壊し終わる処理
		m_breakFlag = false;
	}

	// 無敵の時間
	if (m_invincibleTime >= 0.0f)
	{
		m_invincibleTime -= deltaSecond;
	}
}

void Player::UpdatePlayerState(float deltaSecond)
{
	// 加速度の設定
	float acceleration = m_maxSpeed * 4 * deltaSecond;
	// 減速度の設定
	float deceleration = m_maxSpeed * 3 * deltaSecond;

	// 減速
	PlayerDeceleration(deceleration);

	// 入力から加速、方向転換
	UpdateMovementFromInput(acceleration);

	if (m_diggingFlag)
	{
		// 土を壊す処理
		if (m_pMap->DestroySoil(m_location, m_direction))
		{
			m_diggingFrameTimer = 0.4f;
			m_breakFlag = true;

			// スタミナを消費
			StaminaManager(D_DIG_COST);
		}
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

void Player::UpdateMovementFromInput(float acceleration)
{
	InputManager& input = InputManager::GetInstance();

	// コントローラー自動採掘Hold
	bool digHold = input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Hold || input.GetButtonState(XINPUT_BUTTON_B) == eInputState::Hold;

	// コントローラー上下左右Hold
	bool leftHold = input.GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Hold;
	bool rightHold = input.GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::Hold;
	bool upHold = input.GetButtonState(XINPUT_BUTTON_DPAD_UP) == eInputState::Hold;
	bool downHold = input.GetButtonState(XINPUT_BUTTON_DPAD_DOWN) == eInputState::Hold;

	// コントローラー上下左右Press
	bool leftPress = input.GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Pressed;
	bool rightPress = input.GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::Pressed;
	bool upPress = input.GetButtonState(XINPUT_BUTTON_DPAD_UP) == eInputState::Pressed;
	bool downPress = input.GetButtonState(XINPUT_BUTTON_DPAD_DOWN) == eInputState::Pressed;

#if _DEBUG

	// キー自動採掘
	if (!digHold)digHold = (input.GetKeyState(KEY_INPUT_SPACE) == eInputState::Hold);

	// キー上下左右Hold
	if (!leftHold)leftHold = (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Hold || input.GetKeyState(KEY_INPUT_A) == eInputState::Hold);
	if (!rightHold)rightHold = (input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Hold || input.GetKeyState(KEY_INPUT_D) == eInputState::Hold);
	if (!upHold)upHold = (input.GetKeyState(KEY_INPUT_UP) == eInputState::Hold || input.GetKeyState(KEY_INPUT_W) == eInputState::Hold);
	if (!downHold)downHold = (input.GetKeyState(KEY_INPUT_DOWN) == eInputState::Hold || input.GetKeyState(KEY_INPUT_S) == eInputState::Hold);

	// キー上下左右Press
	if (!leftPress)leftPress = (input.GetKeyState(KEY_INPUT_LEFT) == eInputState::Pressed || input.GetKeyState(KEY_INPUT_A) == eInputState::Pressed);
	if (!rightPress)rightPress = (input.GetKeyState(KEY_INPUT_RIGHT) == eInputState::Pressed || input.GetKeyState(KEY_INPUT_D) == eInputState::Pressed);
	if (!upPress)upPress = (input.GetKeyState(KEY_INPUT_UP) == eInputState::Pressed || input.GetKeyState(KEY_INPUT_W) == eInputState::Pressed);
	if (!downPress)downPress = (input.GetKeyState(KEY_INPUT_DOWN) == eInputState::Pressed || input.GetKeyState(KEY_INPUT_S) == eInputState::Pressed);

#endif

	m_diggingFlag = false;
	// 加速処理
	if (digHold)
	{
		// 自動採掘
		MoveInTheDiggingDirection(acceleration);
		m_diggingFlag = true;
	}
	else
	{
		if (leftHold) m_moveSpeed.x -= acceleration;
		if (rightHold) m_moveSpeed.x += acceleration;
		if (upHold) m_moveSpeed.y -= acceleration;
		if (downHold) m_moveSpeed.y += acceleration;
	}

	// 入力に応じて方向転換
	if (leftPress) m_direction = e_Direction::left;
	if (rightPress) m_direction = e_Direction::right;
	if (upPress) m_direction = e_Direction::up;
	if (downPress) m_direction = e_Direction::down;


	// 速度制限
	if (m_moveSpeed.x > m_maxSpeed)  m_moveSpeed.x = m_maxSpeed;
	if (m_moveSpeed.x < -m_maxSpeed)  m_moveSpeed.x = -m_maxSpeed;
	if (m_moveSpeed.y > m_maxSpeed)  m_moveSpeed.y = m_maxSpeed;
	if (m_moveSpeed.y < -m_maxSpeed)  m_moveSpeed.y = -m_maxSpeed;

	// 斜め移動を禁じる
	if (m_direction == e_Direction::up || m_direction == e_Direction::down) m_moveSpeed.x = 0.0f;
	else if (m_direction == e_Direction::left || m_direction == e_Direction::right) m_moveSpeed.y = 0.0f;

	// 移動中にする
	if (digHold || leftHold || rightHold || upHold || downHold)
		m_animState = e_AnimationState::move;

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
	Vector2D TileLocation = m_pMap->GetTileLocation(position) - Vector2D{ D_BOX_SIZE / 2,D_BOX_SIZE / 2 };

	// 道でなければめり込みを判定
	if (m_pMap->TileType(TileLocation) != e_TileType::road)
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

			return true;
		}

	}

	return false;
}

const int& Player::GetStamina() const
{
	return m_stamina;
}

const int& Player::GetScore() const
{
	return m_score;
}

bool Player::IsStartAnimFinished() const
{
	return m_isStartAnimFinished;
}

bool Player::IsEndAnimFinished() const
{
	return m_isEndAnimFinished;
}

void Player::SetMap(MapData* mapdata)
{
	m_pMap = mapdata;
}
