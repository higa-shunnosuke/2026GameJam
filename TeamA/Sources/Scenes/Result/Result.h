#pragma once
#include "../SceneBase.h"
#include "../../System/Ranking.h"

#include <string>
#include <vector>

class Result : public SceneBase
{
private:

	Ranking* m_ranking;					// ランキングデータ
	PlayData m_currentData;				// 今回のプレイデータ
	int m_rank;							// 順位
	int m_cursorNumber;					// カーソル番号
	bool m_rankingDraw;					// true:ランキング描画

	// 画像
	int m_haikeiImage[2];	// 背景
	int m_scoreImage;		// RESURT SCORE文字
	int m_jewelImage;		// 宝石
	int m_backrockImage;	// ボタン背景
	int m_restartImage;		// RESTART文字
	int m_rankingImage;		// RANKING文字
	int m_titleImage;		// TITLE文字
	int m_moguraImage;		// カーソルアイコン

	//アニメーション
	float m_animeTime;
	int m_animeCount;
	bool m_clickFlag;

	float m_haikeiTime;
	int m_haikeiCount;

	float m_taikiTime;
	int m_taikiCount;


	// サウンド
	// リザルトBGM
	int m_resultBgm;
	// 選択SE
	int m_selectSe;
	// 決定SE
	int m_decisionSe;

public:
	// コンストラクタ
	Result();

	// デストラクタ
	virtual ~Result() = default;

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
	/// <param name="data">受け取るデータ</param>
	/// <returns>渡すデータ</returns>
	virtual PlayData TransitionData(const PlayData* prevdata) override;

};