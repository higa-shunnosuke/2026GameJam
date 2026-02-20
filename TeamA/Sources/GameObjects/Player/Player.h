#pragma once
#include "../ObjectBase.h"
#include "../../Utilitys/Vector2D.h"
#include "../../System/MapData/Direction.h"

class Player : public ObjectBase
{private:

	// スタミナ
	int m_stamina;
	int m_staminaMax;

	// 半径
	float m_radius;

	// 無敵時間
	float m_invincibleTime;

	// 速度
	Vector2D m_moveSpeed;

	// フラグ
	bool m_walkingFlag;
	bool m_digingFlag;
	bool m_flipFlag;

	// アニメーション
	float m_walkAnimTime;
	int m_walkAnimCount;
	float m_drillAnimTime;
	int m_drillAnimCount;
	float m_effectAnimTime;
	int m_effectAnimCount;
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
	void Update() override;

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
	void StaminaManager(int value);

public:
	const int& GetStamina() const;
	const int& GetStaminaMax() const;
};

