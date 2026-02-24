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
	int m_boardImg;				// 板画像
	int m_timerImg;				// タイマー画像
	int m_staminaBarImg[3];		// スタミナバー画像
	int m_staminaFlameImg[2];	// スタミナフレーム画像
	int m_moleIconImg[3];		// モグラアイコン画像
	int m_potatoImg;			// ポテトの画像
	int m_jewelImg;				// ジュエルの画像

	float m_finishAnimeTime;		// finish描画時間

	// サウンド
	int m_Bgm;
	int m_TimeUpSe;

public:
	// コンストラクタ
	InGame();

	// デストラクタ
	virtual ~InGame() = default;

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

	/// <summary>
	/// データの受け渡し
	/// </summary>
	/// <param name="prevData">受け取るデータ</param>
	/// <returns>渡すデータ</returns>
	virtual PlayData TransitionData(const PlayData* prevdata) override;

private:
	/// <summary>
	/// 現在の日付を取得する
	/// </summary>
	/// <returns>yyyy-mm-dd hh:mm:ss</returns>
	std::string GetCurrentDate();

};