#pragma once
#include "../ObjectBase.h"
#include "../../System/InputManager.h"
#include "../../Utilitys/Vector2D.h"
#include "../MapData/Direction.h"
#include "../MapData/MapData.h"

class Player : public ObjectBase
{
private:

	// キャラクターの現在の動作種別を表す列挙型
	enum class e_AnimationState
	{
		idle,
		walk,
		eat
	};

	MapData* m_pMap;		// マップ

	int m_score;			// スコア
	int m_stamina;			// スタミナ
	int m_staminaMax;		// スタミナの最大
	int m_potatoStock;		// 所持しているポテトの数
	float m_invincibleTime;	// スタミナが減少無効果時間


	// 入力
	eInputState m_up;
	eInputState m_down;
	eInputState m_left;
	eInputState m_right;
	eInputState m_digButton;

	// 移動
	Vector2D m_moveSpeed;	// 速度
	float m_maxSpeed;		// 速度の最大
	e_Direction m_direction;// 向き

	bool m_walkingFlag;		// 歩きフラグ
	bool m_diggingFlag;		// 掘るフラグ
	bool m_breakFlag;		// 壊すフラグ
	bool m_flipFlag;		// 反転フラグ

	// アニメーション
	float m_walkAnimTime;
	int m_walkAnimCount;
	float m_diggingAnimTime;
	int m_diggingAnimCount;

	e_AnimationState m_animState;	// 現在再生している動作の種類
	float m_animTimer;				// フレーム切り替え用の経過時間


	Vector2D m_offset;		// 画像のずらす位置

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
	void ApplyInput();

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
	/// スタミナの最大を取得
	/// </summary>
	/// <returns>スタミナの最大</returns>
	const int& GetStaminaMax() { return m_staminaMax; };

	/// <summary>
	/// スコアを取得
	/// </summary>
	/// <returns></returns>
	const int& GetScore() const;

	/// <summary>
	/// マップのインスタンスを受け取る
	/// </summary>
	/// <param name="mapdata"></param>
	void SetMap(MapData* mapdata);
};

