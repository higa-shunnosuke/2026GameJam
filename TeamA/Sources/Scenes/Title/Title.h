#pragma once
#include "../SceneBase.h"


// タイトル
class Title : public SceneBase
{
private:

	// カーソル
	int m_cursorNumber;
	bool m_clickFlag;

	// アニメーション
	int m_animeCount;
	float m_animeTime;
	
	// タイトル画像
	int m_buttonImage;
	int m_uiImage[3];

	// カーソル
	int m_moleImg;		//横向きのモグラ
	int m_drillImg[3];	//横向きのドリル
	int m_effectImage[3];	//採掘エフェクト

	// タイトルロゴ
	int m_logoImg;

	// 背景
	int m_groundImg;			// 地面
	std::vector<int> m_skyImg;	// 空画像


	// サウンド
	int m_titleBgm;		// BGM
	int m_selectSe;		// カーソルSE
	int m_decisionSe;	// 決定SE

	// 入力
	eInputState m_up;
	eInputState m_down;
	eInputState m_decision;

public:
	// コンストラクタ
	Title();

	// デストラクタ
	virtual ~Title() = default;

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
};

