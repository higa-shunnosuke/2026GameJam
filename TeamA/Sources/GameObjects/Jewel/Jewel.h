#pragma once
#include "../ObjectBase.h"

class Jewel : public ObjectBase
{
private:

	float m_animeTime;		// フレーム切り替え用の経過時間
	int m_animeCount;		// 現在のフレーム番号

	float m_animeTime_e;	// フレーム切り替え用の経過時間（エフェクト）
	int m_animeCount_e;		// 現在のフレーム番号（エフェクト）

	int m_emerald_image[4];	// 宝石画像
	int m_effect_image[3];	// エフェクト画像

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Jewel();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Jewel();

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
};

