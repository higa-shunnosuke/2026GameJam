#pragma once
#include "../SceneBase.h"
#include "../../GameObjects/ObjectManager.h"
#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/MapData/MapData.h"

class InGame : public SceneBase
{
private:
	MapData* m_map;
	Player* m_player;

	int m_back_buffer;			// バックバッファ
	std::vector<int> m_skyImg;	// 空画像
	int m_groundImg;			// 地面画像
	int m_timerImg;				// タイマー画像
	int m_staminaBarImg[3];		// スタミナバー画像
	int m_staminaFlameImg[2];	// スタミナフレーム画像
	int m_moleIconImg[3];		// モグラアイコン画像

public:
	// コンストラクタ
	InGame();

	// デストラクタ
	virtual ~InGame() = default;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual SceneType Update(float delta) override;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() const override;

	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() override;

	/// <summary>
	/// 現在のシーンタイプを取得
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual const SceneType GetNowSceneType() const override;

private:

};