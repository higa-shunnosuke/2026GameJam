#pragma once
#include "../ObjectBase.h"
#include "../../System/InputManager.h"
#include "../../Utilitys/Vector2D.h"
#include "../MapData/Direction.h"
#include "../MapData/MapData.h"

class Player : public ObjectBase
{
private:

	MapData* m_map;

	// スコア
	int m_score;

	// スタミナ
	int m_stamina;
	// スタミナの最大
	int m_staminaMax;

	// 無敵時間
	float m_invincibleTime;

	// 速度
	Vector2D m_moveSpeed;
	// 速度の最大
	float m_maxSpeed;

	// 歩きフラグ
	bool m_walkingFlag;
	// 掘るフラグ
	bool m_diggingFlag;
	// 壊すフラグ
	bool m_breakFlag;
	// 反転フラグ
	bool m_flipFlag;

	// アニメーション
	float m_walkAnimTime;
	int m_walkAnimCount;
	float m_diggingAnimTime;
	int m_diggingAnimCount;

	// 向き
	e_Direction m_direction;

	// 画像のずらす位置
	Vector2D m_offset;

	// プレイヤーの画像情報
	int m_idleImage;
	int m_walkImage[2];
	int m_upImage[3];
	int m_downImage[3];

	// ドリルの画像情報
	int m_drillImage[3];
	int m_drillUpImage[3];
	int m_drillDownImage[3];

	// エフェクトの画像情報
	int m_effectImage[3];

	// 操作
	eInputState m_up;
	eInputState m_down;
	eInputState m_left;
	eInputState m_right;
	eInputState m_digButton;

public:
	Player();
	~Player();

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(float delta) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;
	
public:

	/// <summary>
	/// 判定処理
	/// </summary>
	/// <param name="other"></param>
	void OnHitCollision(ObjectBase& other) override;

private:
	/// <summary>
	/// スタミナを加算、減算する
	/// </summary>
	/// <param name="value">加算する値</param>
	void StaminaManager(int value);

	/// <summary>
	/// スコアを加算、減算する
	/// </summary>
	/// <param name="value">加算する値</param>
	void ScoreManager(int value);

	/// <summary>
	/// 全ての入力を各対応変数にまとめる
	/// </summary>
	void ApplyAllInput();

	/// <summary>
	/// アニメーション時間の経過
	/// </summary>
	void LapseAnimation(float deltaTime);

	/// <summary>
	/// プレイヤーの操作
	/// </summary>
	/// <param name="deltaSecond">フレーム秒</param>
	void PlayerOperate(float deltaSecond);

	/// <summary>
	/// プレイヤーの減速
	/// </summary>
	/// <param name="deceleration">減速度</param>
	void PlayerDeceleration(float deceleration);

	/// <summary>
	/// プレイヤーの移動操作
	/// </summary>
	/// <param name="acceleration">加速度</param>
	void PlayerWalkingOperation(float acceleration);

	/// <summary>
	/// プレイヤーの方向転換処理
	/// </summary>
	void PlayerChangeDirection();

	/// <summary>
	/// プレイヤーを特定の方向に転換する処理
	/// </summary>
	/// <param name="direction">向き</param>
	/// <param name="inputState">入力状態</param>
	void ChangeOneDirection(e_Direction direction, eInputState inputState);

	/// <summary>
	/// 掘っている方向に移動する
	/// </summary>
	/// <param name="acceleration">加速度</param>
	/// <param name="deltaSecond">フレーム秒</param>
	void MoveInTheDiggingDirection(float acceleration);

	/// <summary>
	/// ブロックとの当たり判定
	/// </summary>
	/// <param name="deltaSecond">フレーム秒</param>
	void CollisionDetectionWithBlocks(float deltaSecond);
	
	/// <summary>
	/// 押し出し処理
	/// </summary>
	/// <param name="position">ブロックの判定開始位置</param>
	/// <param name="deltaSecond">フレーム秒</param>
	/// <returns>衝突判定ならTRUE</returns>
	bool PlayerPushingByBlocks(Vector2D position, float deltaSecond);

public:
	/// <summary>
	/// 現在のスタミナを取得
	/// </summary>
	/// <returns></returns>
	const int& GetStamina() const;

	/// <summary>
	/// スコアを取得
	/// </summary>
	/// <returns></returns>
	const int& GetScore() const;

	void SetMap(MapData* mapdata);
};

